#include "U_Therapy.h"


bool U_Therapy::canAssign(Lists& lists)
{
    return !lists.U_Devices.isEmpty(); 
}

void U_Therapy::MoveToWait(Scheduler* sch, Patient* p){
    sch->AddToWait_U(p);
}