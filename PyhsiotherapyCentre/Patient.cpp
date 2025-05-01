#include "Patient.h"
#include <cctype> // For toupper

int Patient::IDGenerator = 0;

Patient::Patient(char PType, int PT, int VT) {
    ID = ++IDGenerator;
    this->PType = toupper(PType);
    this->PT = PT;
    this->VT = VT;
    state = Idle;
    CurrTreatment = nullptr;
    TT = 0;
    WT = 0;
    FT = 0;
    Rescheduled = 0;
}

void Patient::AddTreatment(Treatment* treatment) {
    if (Treatments.isEmpty())
        CurrTreatment = treatment;

    Treatments.enqueue(treatment);
}

void Patient::RemoveTreatment() {
    if (Treatments.isEmpty())
        return;

    Treatment* temp;
    Treatments.dequeue(temp);

    Treatments.peek(CurrTreatment);
}

bool Patient::getCurrentTreatment(Treatment*& treatment) {
    if (Treatments.isEmpty())
        return false;
    treatment = CurrTreatment;
    return true;
}

void Patient::setLastTreatment(char treat) {
    LastTreatment = toupper(treat);
}

char Patient::LastTreatmentType() {
    return LastTreatment;
}

void Patient::setState(pState state) {
    this->state = state;
}

Patient::pState Patient::getState() const {
    return state;
}

int Patient::TreatmentDuration() {
    return CurrTreatment->GetDuration();
}

int Patient::getPT() const {
    return PT;
}

int Patient::getID() const {
    return ID;
}

void Patient::setPT(int pt) {
    PT = pt;
}

int Patient::getVT() const {
    return VT;
}

void Patient::setVT(int vt) {
    VT = vt;
}

char Patient::getPType() const {
    return PType;
}

int Patient::getFT() const {
    return FT;
}

void Patient::setFT(int ft) {
    FT = ft;
}

int Patient::getWT() const {
    return WT;
}

void Patient::setWT(int wt) {
    WT = wt;
}

int Patient::getTT() const {
    return TT;
}

void Patient::setTT(int tt) {
    TT = tt;
}

bool Patient::isCancelled() const {
    return Cancelled;
}

void Patient::setCancelled(bool cancelled) {
    Cancelled = cancelled;
}

int Patient::getRescheduled() const {
    return Rescheduled;
}

void Patient::incRescheduled() {
    Rescheduled++;
}

std::ostream& operator<<(std::ostream& out, Patient& p) {
    if (p.state == Patient::pState::Idle) {
        out << 'P' << p.ID << '_' << p.VT;
        return out;
    }

    if (p.state == Patient::pState::Serv) {
        UEResource* resource = p.CurrTreatment->GetAssResource();

        out << 'P' << p.ID << '_';
        out << resource->getType() << resource->getID();

        return out;
    }

    out << p.ID;

    return out;
}