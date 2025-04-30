#pragma once
#include "Treatment.h"
#include "Scheduler.h"

class X_Therapy : public Treatment
{
	
public:
	X_Therapy(int duration):Treatment(duration,'X')
	{ }
	// No Representation for these two is required in Phase 1
	bool canAssign(Lists& lists) override
	{
		return !lists.X_Rooms.isEmpty(); 
	}
	void MoveToWait(Scheduler* sch, Patient* p)  override
	{ 
		sch->AddToWait_X(p);
	}
};

