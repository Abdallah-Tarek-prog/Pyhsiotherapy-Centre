#pragma once
#include "LinkedQueue.h"
#include "Patient.h"

class M1Queue : public LinkedQueue<Patient*>
{
protected:
	int TL; //Treatment Latency
public:
	M1Queue():LinkedQueue()
	{ TL = 0; }

	void enqueue(Patient* pat)
	{
		LinkedQueue<Patient*>::enqueue(pat);
		TL	+= pat->TreatmentDuration();
	}

	void dequeue(Patient* pat)
	{
		LinkedQueue<Patient*>::dequeue(pat);
		TL -= pat->TreatmentDuration();
	}

	int calculateTL() const {
		return TL;
	}


	void InsertSorted(Patient* pat,int priority)
	{
		if (isEmpty())
		{
			enqueue(pat);
			return;
		}
		count++;
		// The Patient should be inserted with given priortiy and sorted with respect to PT
		// this implementation sorts decscendingly like 9 8 7 6
		if (frontPtr->getItem()->getPT() < priority)
		{
			Node<Patient*>* temp = new Node<Patient*>(pat,frontPtr);
			frontPtr = temp;
			return;
		}

		Node<Patient*>* current = frontPtr->getNext();
		Node<Patient*>* becurrent = frontPtr; // becurrent is short for before current

		while (current && current->getItem()->getPT() >= priority) 
		{
			becurrent = becurrent->getNext();
			current = current->getNext();
		}

		if (!current) // The element has least priority
		{
			becurrent ->setNext( new Node<Patient*>(pat, NULL) );
			backPtr = becurrent->getNext();
			return;
		}

		if (current->getItem()->getPT() < priority) // We found the right position for the element
		{
			Node<Patient*>* temp = new Node<Patient*>(pat, current);
			becurrent->setNext(temp);
			return;
		}

		// Notes: Late Patients are sorted with their (PT+late penalty) 
		// , but  the pateint's (PT+ Penalty) is compared to other's PT whether they were late or early 

		//	 In case of Equal priority like 9 8(1) 7 and we want to insert 8(2) 
		//	The Order will be 9 8(1) 8(2) 7



	}

};

