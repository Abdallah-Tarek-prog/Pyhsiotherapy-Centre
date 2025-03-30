#pragma once
#include "Treatment.h"
class U_Therapy : public Treatment
{
public:
	U_Therapy(int duration) :Treatment(duration)
	{
	}
	bool canAssign()
	{
	}
	void MoveToWait(Patient* patient)
	{
	}
};

