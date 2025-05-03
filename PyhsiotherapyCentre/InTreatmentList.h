#pragma
#pragma once
#include "priQueue.h"
#include "Patient.h"

class InTreatmentList : public priQueue<Patient*>
{
public:
	InTreatmentList() : priQueue(){}

	// Device Go Boom function
	bool FailDevice(int index, Patient*& Delinked)
	{
		if (index == 0)
		{
			int _;
			// Cancelling the fail device if it's not U or E
			 Patient* p = head->getItem(_);

			 Treatment* t;
			 p->getCurrentTreatment(t);
			
			 if (t->GetType() == 'X')
				 return false;

			 // Dequeuing the last element
			 priNode<Patient*>* temp = head;

			 Delinked = temp->getItem(_);

			 head = head->getNext();
			 delete temp;


			 count--;

			 return true;
		}


		int i = 1;

		priNode<Patient*>* curr = head->getNext();
		priNode<Patient*>* prev = head;

		while (i != index) {
			curr = curr->getNext();
			prev = prev->getNext();

			i++;
		}

		// Cancelling the fail device if it's not U or E
		int _;
		Patient* p = curr->getItem(_);

		Treatment* t;
		p->getCurrentTreatment(t);

		if (t->GetType() == 'X')
			return false;

		// Removing the Treatment at this index
		prev->setNext(curr->getNext());
		Delinked = curr->getItem(_);
		delete curr;
		
		count--;

		return true;
	}

};

