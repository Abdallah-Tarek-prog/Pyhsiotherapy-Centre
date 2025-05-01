#pragma once
#include "Treatment.h"
#include "Scheduler.h"

class E_Therapy : public Treatment
{
public:
	E_Therapy(int duration) :Treatment(duration,'E')
	{
	}
	bool canAssign(Lists& lists) override;
	void MoveToWait(Scheduler* sch, Patient* p) override;
};

