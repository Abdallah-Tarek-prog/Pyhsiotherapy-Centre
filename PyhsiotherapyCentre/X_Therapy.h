#pragma once
#include "Treatment.h"
class X_Therapy : public Treatment
{
	
public:
	X_Therapy(int duration):Treatment(duration)
	{ }
	bool canAssign() 
	{ }
	void MoveToWait(Patient* patient) 
	{ }
};

