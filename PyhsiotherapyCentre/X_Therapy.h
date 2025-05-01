#pragma once
#include "Treatment.h"
#include "Scheduler.h"

class X_Therapy : public Treatment
{
	
public:
	X_Therapy(int duration):Treatment(duration,'X')
	{ }
	// No Representation for these two is required in Phase 1
	bool canAssign(Lists& lists) override;
	void MoveToWait(Scheduler* sch, Patient* p)  override;
};

