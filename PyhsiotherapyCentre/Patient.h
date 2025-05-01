#pragma once
#include <iostream>
#include "LinkedQueue.h"
#include "Treatment.h"

class Patient {
public:
    enum pState { Early, Late, Idle, Wait, Serv, Finished };

private:
    int ID;
    int PT; // Appointment Time
    int VT; // Arrival Time
    int FT; // Finish Time
    int WT; // Waiting Time
    int TT; // Treatment Time

    bool Cancelled;
    int Rescheduled;

    static int IDGenerator;
    LinkedQueue<Treatment*> Treatments;
    Treatment* CurrTreatment;
    pState state;
    char PType; // R for recovering, N for Normal
    char LastTreatment;

public:
    Patient(char PType, int PT, int VT);

    void AddTreatment(Treatment* treatment);
    void RemoveTreatment();
    bool getCurrentTreatment(Treatment*& treatment);
    void setLastTreatment(char treat);
    char LastTreatmentType();
    void setState(pState state);
    pState getState() const;
    int TreatmentDuration();
    int getPT() const;
    int getID() const;
    void setPT(int pt);
    int getVT() const;
    void setVT(int vt);
    char getPType() const;
    int getFT() const;
    void setFT(int ft);
    int getWT() const;
    void setWT(int wt);
    int getTT() const;
    void setTT(int tt);
    bool isCancelled() const;
    void setCancelled(bool cancelled);
    int getRescheduled() const;
    void incRescheduled();

    friend std::ostream& operator<<(std::ostream& out, Patient& p);
};