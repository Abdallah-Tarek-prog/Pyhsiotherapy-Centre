#pragma once
#include <iostream>
#include"LinkedQueue.h"
#include"Treatment.h"

class Patient
{
public:
	enum pState { Early, Late, Idle, Wait, Finished };
private:
	int ID;
	int PT;
	int VT;
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

	void setPT(int pt)
	{ PT = pt; }

	int getVT() const 
	{ return VT; }

	void setVT(int vt)
	{ VT = vt; }

	void printWithTreatment() {
		if (!CurrTreatment || !CurrTreatment->GetAssResource())
			return;

		UEResource* resource = CurrTreatment->GetAssResource();

		std::cout << 'P' << ID << '_';
		std::cout << resource->getType() << resource->getID();
	}

	void printWithVT() {
		std::cout << 'P' << ID << '_' << VT;
	}

	friend std::ostream& operator<<(std::ostream& out, Patient& p) {
		out << p.ID;

		return out;
	}
};
 int Patient::IDGenerator=0;
