#pragma once
#include "LinkedQueue.h"
#include "priQueue.h"
#include "MpriQueue1.h"
#include "M1Queue.h"
#include "Patient.h"

class Scheduler
{
    private:
        int timeStep;
        LinkedQueue<Patient*> allPatientsList;
        MpriQueue1<Patient*> earlyList;
        //M1Queue<Patient*> U_WaitingList;
        //M1Queue<Patient*> E_WaitingList;
        //M2Queue<Patient*> X_WaitingList;
        priQueue<Patient*> lateList;
        
    public:
        Scheduler()
        {
            srand(time(0));
        }

        ~Scheduler()
        {
        }

        void MoveFromAll(){
            Patient* topPatient;
            
            while(allPatientsList.peek(topPatient)){
                if(topPatient->getVT() == timeStep){
                    Patient* temp;
                    allPatientsList.dequeue(temp);
                    
                    if(topPatient->getVT() == topPatient->getPT()){
                        RandomWaiting(topPatient);
                        continue;
                    }


                    if(topPatient->getVT() > topPatient->getPT()){
                        int penalty = (topPatient->getVT() - topPatient->getPT()) / 2;
                        lateList.enqueue(topPatient, topPatient->getVT() + penalty);
                    }else{
                        earlyList.enqueue(topPatient, topPatient->getPT());
                    }
                }
            }
        }
        

      void simulateTimestep()
       {    
        MoveFromAll();

        Patient * next;

        int X = rand() % 101;

        switch (X / 10) {
            case 0:
                earlyList.dequeue(next);
                RandomWaiting(next);
                break;
            case 1:
                lateList.dequeue(next);
                RandomWaiting(next);
                break;
            case 2:
                    
                break;
            case 3:
                    
                break;
            case 4:
                    
                break;
            case 5:
                    
                break;
            case 6:
                    
                break;
            case 7:
                    
                break;
            case 8:
                    
                break;
            case 9:
                    
                break;
            case 10:
                    
                break;
            default:
                break;
        }
        }

        void RandomWaiting(Patient* p, bool fromTreatment = false) {
            int randomNumber = (rand() % 101);

            if (fromTreatment || p->getPT() <= p->getVT()) {
                if (randomNumber < 33) {
                    //E_WaitingList.enqueue(p);
                }

                if (randomNumber >= 33 && randomNumber < 66) {
                    //U_WaitingList.enqueue(p);
                }

                if (randomNumber > 66) {
                    //X_WaitingList.enqueue(p)
                }
            }
            else {
                int penalty = (p->getVT() - p->getPT()) / 2;

                if (randomNumber < 33) {
                    //E_WaitingList.InsertSorted(p, p->getPT() + penalty);
                }

                if (randomNumber >= 33 && randomNumber < 66) {
                    //U_WaitingList.InsertSorted(p, p->getPT() + penalty);
                }

                if (randomNumber > 66) {
                    //X_WaitingList.InsertSorted(p, p->getPT() + penalty);
                };
            }
        }

};

