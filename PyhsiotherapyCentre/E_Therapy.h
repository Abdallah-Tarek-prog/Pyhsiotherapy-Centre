#pragma once
#include "Treatment.h"
#include "Scheduler.h"

class E_Therapy : public Treatment
{
public:
public:
	E_Therapy(int duration, Patient* sch) :Treatment(duration, sch)
	{
	}
	// No Representation for these two is required in Phase 1
	bool canAssign()
	{
		return true; 
	}
	void MoveToWait(Scheduler* sch) override

	{
		
	}
};

