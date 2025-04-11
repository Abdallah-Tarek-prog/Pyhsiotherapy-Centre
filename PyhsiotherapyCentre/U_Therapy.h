#pragma once
#include "Treatment.h"
#include "Scheduler.h"

class U_Therapy : public Treatment
{
public:
	U_Therapy(int duration) :Treatment(duration)
	{
	}
	// No Representation for these two is required
	bool canAssign()
	{
		return true; 
	}
	void MoveToWait(Scheduler* sch) override
	{
	}
};

