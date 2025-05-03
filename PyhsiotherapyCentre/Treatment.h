#pragma once
#include <iostream>

#include"XResource.h" // it already includes UEResource

struct Lists;
class Scheduler;
class Patient;

class Treatment
{
private:
	int duration;
	int ST; // Assignement Time
	UEResource* AssResource; // assigned resource
	char Type;	// U, E ,X
public:
	Treatment(int Duration,char type)
	{
		AssResource = NULL;
		ST = -1;
		duration = Duration;
		this->Type = type;
	}
	virtual bool canAssign(Lists& lists)=0;
	virtual void MoveToWait(Scheduler* PTR, Patient* p)=0;
	void setST(int time)
	{
		ST = time;
	}
	int GetST() const
	{
		return ST;
	}
	char GetType()const
	{
		return Type;
	}
	int GetDuration() const
	{
		return duration;
	}

	void SetDuration(int val) 
	{
		duration = val;
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

