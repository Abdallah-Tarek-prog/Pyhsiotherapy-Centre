#pragma once
#include "Treatment.h"
class X_Therapy : public Treatment
{
	
public:
	X_Therapy(int duration,Scheduler* sch):Treatment(duration,sch)
	{ }
	bool canAssign() 
	{ }
	void MoveToWait(Patient* patient) 
	{ }
};

