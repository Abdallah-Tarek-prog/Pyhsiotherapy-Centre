#pragma once
#include "M1Queue.h"
#include "Patient.h"

class M2Queue : public M1Queue
{

	public:

	void Cancel(int index,Patient*& Delinked)
	{
		if (index == 0)
		{
			Delinked = frontPtr->getItem();
			Node<Patient*>* temp = frontPtr;
			frontPtr=frontPtr->getNext();
			count--;
			delete temp;
			return;
		}
		Node<Patient*>* current = frontPtr->getNext();
		Node<Patient*>* becurrent = frontPtr;
		int i = 1;
		while (i != index)
		{
			current = current->getNext();
			becurrent = becurrent->getNext();
			i++;
		}
		becurrent->setNext(current->getNext());
		Delinked = current->getItem();
		count--;
		if (index == count) {
			backPtr = becurrent;
		}
		delete current;
	}
	
};

