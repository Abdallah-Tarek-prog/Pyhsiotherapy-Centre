#pragma once
#include <iostream>

#include"XResource.h" // it already includes UEResource
class Scheduler;
class Patient;

class Treatment
{
private:
	Patient* pPatient;
	int duration;
	int ST; // Assignement Time
	UEResource* AssResource; // assigned resource
public:
	Treatment(int Duration,Patient* PTR)
	{
		AssResource = NULL;
		pPatient = PTR;
		ST = -1;
		duration = Duration;
	}
	virtual bool canAssign()=0;
	virtual void MoveToWait(Scheduler* PTR)=0;
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

	friend std::ostream& operator<<(std::ostream& out,const  Treatment& t) {
		UEResource* resource = t.GetAssResource();

		out << 'P' << *(t.pPatient) << '_';
		out << resource->getType()<< resource->getID();

		return out;
	}
};

