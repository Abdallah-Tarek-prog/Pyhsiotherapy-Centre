#pragma once
#include "M1Queue.h"
#include "Patient.h"

class M2Queue : public M1Queue
{

	public:

	bool Cancel(int index,Patient*& Delinked)
	{
		if (index == 0)
		{
			if (frontPtr->getItem()->LastTreatmentType() != 'X')
				return false;

			Delinked = frontPtr->getItem();
			Node<Patient*>* temp = frontPtr;
			frontPtr=frontPtr->getNext();
			count--;
			delete temp;
			TL -= Delinked->TreatmentDuration();
			return true;
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

		if (current->getItem()->LastTreatmentType() != 'X')	//Checking before Cancelling
		return false;

		becurrent->setNext(current->getNext());
		Delinked = current->getItem();
		count--;
		if (index == count) {
			backPtr = becurrent;
		}
		delete current;
		TL -= Delinked->TreatmentDuration();
		return true;
	}
	
};

