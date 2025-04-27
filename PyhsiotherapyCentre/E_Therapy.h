#pragma once
#include "Treatment.h"
#include "Scheduler.h"

class E_Therapy : public Treatment
{
public:
public:
	E_Therapy(int duration) :Treatment(duration,'E')
	{
	}
	// No Representation for these two is required in Phase 1
	bool canAssign(Lists& lists) override
	{
		return !lists.E_Deivces.isEmpty(); 
	}
	void MoveToWait(Scheduler* sch) override
	{
	}
};

