#pragma once
#include <iostream>
#include"LinkedQueue.h"
#include"Treatment.h"

class Patient
{
public:
	enum pState { Early, Late, Idle, Wait, Serv ,Finished };
private:
	int ID;	
	int PT;	// Appointment Time
	int VT;	// Arrival Time

	int FT;	// Finish Time
	int WT; // Waiting Time
	int TT; // Treatment Time	// Can't be the summation of Treatments' duration because he may cancel X-treatment
	bool Cancelled;
	bool Rescheduled;

	static int IDGenerator;
	LinkedQueue<Treatment*> Treatments;
	Treatment* CurrTreatment;
 	pState state;
	char PType; // R for recovering  ,   N for Normal
	
public:
	Patient(char PType, int PT, int VT)
	{
		ID = ++IDGenerator;
		this->PType = toupper(PType);
		this->PT = PT;
		this->VT = VT;
		state = Idle;
		CurrTreatment = NULL;
		// All patients when created are idle and they still idle in all patients list 
		// until their VT becomes equal to the timestep
		
	}

	void AddTreatment(Treatment* treatment) {
		if (Treatments.isEmpty())
			CurrTreatment = treatment;

		Treatments.enqueue(treatment);
	}

	void RemoveTreatment() {
		if (Treatments.isEmpty())
			return;

		Treatment* temp;
		Treatments.dequeue(temp);

		Treatments.peek(CurrTreatment);
	}

	char LastTreatmentType()
	{
		LinkedQueue<Treatment*>temp;
		Treatment* treat;
		while (Treatments.dequeue(treat))
		{
			temp.enqueue(treat);
		}
		char LastType=treat->GetType(); // Last treatment type

		while (temp.dequeue(treat))
		{
			Treatments.enqueue(treat);
		}
		return LastType;
	}

	void setState(pState state)
	{
		this->state = state;
	}
	int TreatmentDuration()
	{
		return CurrTreatment->GetDuration();
	}

	int getPT() const
	{ return PT; }

	int getID() const
	{
		return ID;
	}
	void setPT(int pt)
	{ PT = pt; }

	int getVT() const 
	{ return VT; }

	void setVT(int vt)
	{ VT = vt; }

	char getPType()const
	{
		return PType;
	}

	int getFT() const { return FT; }
	void setFT(int ft) { FT = ft; }

	int getWT() const { return WT; }
	void setWT(int wt) { WT = wt; }

	int getTT() const { return TT; }
	void setTT(int tt) { TT = tt; }

	bool isCancelled() const { return Cancelled; }
	void setCancelled(bool cancelled) { Cancelled = cancelled; }

	bool isRescheduled() const { return Rescheduled; }
	void setRescheduled(bool rescheduled) {
		Rescheduled = rescheduled;
	}

	friend std::ostream& operator<<(std::ostream& out, Patient& p) {

		if (p.state == pState::Idle) {
		
			out << 'P' << p.ID << '_' << p.VT;
			return out;
		}

		if (p.state == pState::Serv) {
			UEResource* resource = p.CurrTreatment->GetAssResource();

			std::cout << 'P' << p.ID << '_';
			std::cout << resource->getType() << resource->getID();
		
			return out;
		}


		out << p.ID;

		return out;
	}
};
 int Patient::IDGenerator=0;
