#pragma once
#include "Treatment.h"
class U_Therapy : public Treatment
{
public:
	U_Therapy(int duration, Scheduler* sch) :Treatment(duration, sch)
	{
	}
	bool canAssign()
	{
	}
	void MoveToWait(Patient* patient)
	{
	}
};

