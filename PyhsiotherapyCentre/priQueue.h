#pragma once
#include "priNode.h"

template <typename T>
void defaultPriFormatter(T* item) {
	std::cout << *item;
}

template <typename T>
void defaultPriFormatter(T item) {
	std::cout << item;
}

//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
protected:
	priNode<T>* head;
	int count;
public:
	priQueue() : head(nullptr) {
		count = 0;
	}

	~priQueue() {
		T tmp;
		int p;
		while (dequeue(tmp, p))
		{
			count--;
		}
	}

	//insert the new node in its correct position according to its priority
	// This is insert Sorted function written in normal linked lists

	void enqueue(const T& data, int priority) {
		priNode<T>* newNode = new priNode<T>(data, priority);

		count++;

		if (head == nullptr || priority > head->getPri()) {
			newNode->setNext(head);
			head = newNode;
			return;
		}

		priNode<T>* current = head;
		while (current->getNext() && priority <= current->getNext()->getPri()) {
			current = current->getNext();
		}
		newNode->setNext(current->getNext());
		current->setNext(newNode);
	}

	bool dequeue(T& topEntry, int& pri) {
		if (isEmpty())
			return false;

		count--;
		topEntry = head->getItem(pri);
		priNode<T>* temp = head;
		head = head->getNext();
		delete temp;
		return true;
	}

	bool peek(T& topEntry, int& pri) {
		if (isEmpty())
			return false;

		topEntry = head->getItem();
		pri = head->getPri();
		return true;
	}

	bool isEmpty() const {
		return head == nullptr;
	}

	int getCount() const { return count; }

	void print(void (*formatter)(const T) = defaultPriFormatter, int limit = -1) const {
		priNode<T>* current = head;

		if (limit == -1) limit = count;

		while (current && limit--) {
			int temp ;

			formatter(current->getItem(temp));
			cout << ", ";
			current = current->getNext();
		}
	}
};
