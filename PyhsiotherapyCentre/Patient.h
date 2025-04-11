#pragma once
#include"LinkedQueue.h"
#include"Treatment.h"

class Patient
{
	
private:
	int ID;
	int PT;
	int VT;
	static int IDGenerator;
	LinkedQueue<Treatment*> Treatments;
	Treatment* CurrTreatment;
	enum pState { Early, Late, Idle, Wait, Finished };
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
		Treatments.enqueue(treatment);
	}

	void assign_late()
	{

	}

	/*int TreatmentDuration() // Needed for phase 2
	{
		return CurrTreatment->GetDuration();//  logic like that
	}*/

	int getPT() const
	{ return PT; }

	void setPT(int pt)
	{ PT = pt; }

	int getVT() const 
	{ return VT; }

	void setVT(int vt)
	{ VT = vt; }

	friend std::ostream& operator<<(std::ostream& out, Patient& p) {
		out << p.ID;

		return out;
	}
};
 int Patient::IDGenerator=0;
