#pragma once
#include "Treatment.h"
class E_Therapy : public Treatment
{
public:
public:
	E_Therapy(int duration, Patient* sch) :Treatment(duration, sch)
	{
	}
	bool canAssign()
	{
	}
	void MoveToWait(Scheduler* sch) override
	{
	}
};

