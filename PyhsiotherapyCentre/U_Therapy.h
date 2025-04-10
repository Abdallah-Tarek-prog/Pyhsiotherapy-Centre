#pragma once
#include "Treatment.h"
#include "Scheduler.h"

class U_Therapy : public Treatment
{
public:
	U_Therapy(int duration, Patient* pPatient) :Treatment(duration, pPatient)
	{
	}
	bool canAssign()
	{
	}
	void MoveToWait(Scheduler* sch) override
	{
	}
};

