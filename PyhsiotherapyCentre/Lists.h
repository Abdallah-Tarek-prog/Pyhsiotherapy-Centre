#pragma once
#include "LinkedQueue.h"
#include "ArrayStack.h"
#include "MpriQueue1.h"
#include "M1Queue.h"
#include "M2Queue.h"
#include "priQueue.h"

#include "Patient.h"
#include "UEResource.h"
#include "XResource.h"
#include "Treatment.h"

struct Lists {
    LinkedQueue<Patient*> allPatientsList;
    ArrayStack<Patient*> finishedList;

    MpriQueue1<Patient*> earlyList;
    priQueue<Patient*> lateList;

    M1Queue U_WaitingList;
    M1Queue E_WaitingList;
    M2Queue X_WaitingList;

    LinkedQueue<UEResource*> U_Deivces;
    LinkedQueue<UEResource*> E_Deivces;
    LinkedQueue<XResource*> X_Rooms;

    priQueue<Patient*> inTreatmentList;
};