#pragma once
#include "Treatment.h"
class E_Therapy : public Treatment
{
public:
public:
	E_Therapy(int duration, Scheduler* sch) :Treatment(duration, sch)
	{
	}
	bool canAssign()
	{
	}
	void MoveToWait(Patient* patient)
	{
	}
};

