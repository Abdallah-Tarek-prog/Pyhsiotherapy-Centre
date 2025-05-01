#pragma once
#include "priQueue.h"
#include "Patient.h"

class MpriQueue1 : public priQueue<Patient*>
{
public:
	MpriQueue1() :priQueue()
	{
		
	}
	bool Reschedule(int index)
	{	
		int _pri;
		if (index == 0)
		{
			priNode<Patient*>* temp=head;
			if(temp->getItem(_pri)->getRescheduled() >= 3) return false;
			head = head->getNext();
			// Delinking 
			count--;
			// incRescheduled
			temp->getItem(_pri)->incRescheduled();
			// Generating new PT from PT+1 up to 3*PT		// Randomly but limited 
			int NewPT = temp->getItem(_pri)->getPT();
			NewPT = NewPT + 1 + rand() % (2 * NewPT);
			enqueue(temp->getItem(_pri), -1 * NewPT);			//Priority Negated
			delete temp;
			return true;
		}

		int i = 1;
		priNode<Patient*>* current = head->getNext();
		priNode<Patient*>* becurrent = head;	// becurrent is short for Before current 

		while (i != index)
		{
			current = current->getNext();
			becurrent = becurrent->getNext();
			i += 1;
		}
		if(current->getItem(_pri)->getRescheduled() >= 3) return false;
		becurrent->setNext(current->getNext());	// De-link current 
		count--;
		current->getItem(_pri)->incRescheduled();
		int NewPT = current->getItem(_pri)->getPT();
		NewPT = NewPT + 1 + rand() % (2 * NewPT);
		enqueue(current->getItem(_pri), -1 * NewPT);			//Priority Negated
		delete current;
		return true;


		// Reschedule implementation isn't the most Optimized 
		// because we don't have to compare from the beginning when sorting again ( it is still O(n) though )
	}
};

