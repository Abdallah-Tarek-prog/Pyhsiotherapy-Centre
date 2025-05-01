#include "E_Therapy.h"
#include "Scheduler.h"


bool E_Therapy::canAssign(Lists& lists) 
	{
		return !lists.E_Devices.isEmpty(); 
	}
void E_Therapy::MoveToWait(Scheduler* sch, Patient* p) 
{
    sch->AddToWait_E(p);
}