#pragma once
#include "LinkedQueue.h"
#include "Patient.h"

class M1Queue : public LinkedQueue<Patient*>
{
private:
	int TL;
public:
	M1Queue():LinkedQueue()
	{ TL = 0; }
	void enqueue(Patient* pat)
	{
		LinkedQueue<Patient*>::enqueue(pat);
		// TODO : Adding some value to TL
		int duration=
	}
	void dequeue(Patient* pat)
	{
		LinkedQueue<Patient*>::dequeue(pat);
		// TODO : Decrementing some value from TL
	}
	void InsertSorted()
	{

	}

};

