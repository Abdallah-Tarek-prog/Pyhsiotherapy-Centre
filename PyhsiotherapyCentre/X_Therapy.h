#pragma once
#include "Treatment.h"
class X_Therapy : public Treatment
{
	
public:
	X_Therapy(int duration,Patient* pPatient):Treatment(duration,pPatient)
	{ }
	bool canAssign() 
	{ }
	void MoveToWait(Scheduler* sch)  override
	{ }
};

