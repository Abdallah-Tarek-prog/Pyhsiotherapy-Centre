#pragma once
#include "Treatment.h"
#include "Scheduler.h"
class U_Therapy : public Treatment
{
public:
	U_Therapy(int duration) :Treatment(duration, 'U')
	{
	}
	// No Representation for these two is required in phase 1
	bool canAssign(Lists& lists) override;
	void MoveToWait(Scheduler* sch, Patient* p) override;
};

