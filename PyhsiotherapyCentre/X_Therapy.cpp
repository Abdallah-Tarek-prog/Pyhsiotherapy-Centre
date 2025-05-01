#include "X_Therapy.h"


bool X_Therapy::canAssign(Lists& lists)
{
    return !lists.X_Rooms.isEmpty(); 
}

void X_Therapy::MoveToWait(Scheduler* sch, Patient* p){
    sch->AddToWait_X(p);
}