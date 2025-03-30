#pragma once
#include"XResource.h" // it already includes UEResource
#include"Patient.h"
#include"Scheduler.h"
class Treatment
{
private:
	Scheduler* Sch;
	int duration;
	int ST; // Assignement Time
	UEResource* AssResource; // assigned resource
public:
	Treatment(int Duration,Scheduler* PTR)
	{
		AssResource = NULL;
		Sch= PTR;
		ST = -1;
		duration = Duration;
	}
	virtual bool canAssign()=0;
	virtual void MoveToWait(Patient* patient)=0;
	void setST(int time)
	{
		ST = time;
	}
	int GetST() const
	{
		return ST;
	}
	int GetDuration() const
	{
		return duration;
	}
	UEResource* GetAssResource() const
	{
		return AssResource;
	}
	void setAssResource(UEResource* res)
	{
		AssResource = res;
	}
};

