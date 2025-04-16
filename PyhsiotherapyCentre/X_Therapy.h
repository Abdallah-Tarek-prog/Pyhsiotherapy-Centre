#pragma once
#include "Treatment.h"
#include "Scheduler.h"

class X_Therapy : public Treatment
{
	
public:
	X_Therapy(int duration):Treatment(duration,'X')
	{ }
	// No Representation for these two is required in Phase 1
	bool canAssign()
	{
		return true; 
	}
	void MoveToWait(Scheduler* sch)  override
	{ }
};

