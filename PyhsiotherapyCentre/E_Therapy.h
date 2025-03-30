#pragma once
#include "Treatment.h"
class E_Therapy : public Treatment
{
public:
public:
	E_Therapy(int duration) :Treatment(duration)
	{
	}
	bool canAssign()
	{
	}
	void MoveToWait(Patient* patient)
	{
	}
};

