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
	// FT = total waiting Time + total treatment Time
	// so We will calculate the total treatment time

	bool Cancelled;
	bool Rescheduled;

	static int IDGenerator;
	LinkedQueue<Treatment*> Treatments;
	Treatment* CurrTreatment;
 	pState state;
	char PType; // R for recovering  ,   N for Normal
	char LastTreatment;
	
public:
	Patient(char PType, int PT, int VT)
	{
		ID = ++IDGenerator;
		this->PType = toupper(PType);
		this->PT = PT;
		this->VT = VT;
		state = Idle;
		CurrTreatment = NULL;
		TT = 0;
		WT = 0;
		FT = 0;
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

	bool getCurrentTreatment(Treatment*& treatment) {
		if (Treatments.isEmpty())
			return false;
		treatment = CurrTreatment;	// Check that this is always updated
		return true;
	}
	void setLastTreatment(char treat)
	{
		LastTreatment = toupper(treat);
	}
	char LastTreatmentType()
	{	// Last inserted treatment instead of looping on all the list becasue it may be modified
		// in case of Recovering patient when sorting
		return LastTreatment;
	}

	void setState(pState state)
	{
		this->state = state;
	}

	pState getState() const { return state; }

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
