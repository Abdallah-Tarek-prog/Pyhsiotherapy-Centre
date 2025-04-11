#pragma once
#include "priQueue.h"
#include "Patient.h"
template <class T>
class MpriQueue1 : public priQueue<Patient*>
{
public:
	MpriQueue1() :priQueue()
	{
		
	}
	void Reschedule(int index)
	{	

		if (index == 0)
		{
			Node<Patient*>* temp=head;
			head = head->getNext();
		// Generating new PT from PT+1 up to 3*PT		// Randomly but limited 
			int NewPT = temp->getItem()->getPT();
			NewPT = NewPT + 1 + rand() % (2 * NewPT);
			enqueue(temp->getItem(), -1 * NewPT);			//Priority Negated
			return;
		}

		int i = 1;
		Node<Patient*>* current = head->getNext();
		Node<Patient*>* becurrent = head;	// becurrent is short for Before current 

		while (i != index)
		{
			current = current->getNext();
			becurrent = becurrent->getNext();
			i += 1;
		}
		becurrent->setNext(current->getNext());	// De-link current 
		
		int NewPT = current->getItem()->getPT();
		NewPT = NewPT + 1 + rand() % (2 * NewPT);
		enqueue(current->getItem(), -1 * NewPT);			//Priority Negated
		return;


		// Reschedule implementation isn't the most Optimized 
		// because we don't have to compare from the beginning when sorting again ( it is still O(n) though )
	}
};

