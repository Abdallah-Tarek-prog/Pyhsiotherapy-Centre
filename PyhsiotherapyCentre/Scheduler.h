#pragma once
#include "LinkedQueue.h"
#include "priQueue.h"
#include "MpriQueue1.h"
#include "M1Queue.h"
#include "ArrayStack.h"
#include "Patient.h"

class Scheduler
{
    private:
        int timeStep;
        LinkedQueue<Patient*> allPatientsList;
        MpriQueue1<Patient*> earlyList;
        M1Queue U_WaitingList;
        M1Queue E_WaitingList;
        M2Queue X_WaitingList;
        priQueue<Patient*> lateList;
        priQueue<Patient *> inTreatementList;
        ArrayStack<Patient *> finishList;
        
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
                        RandomWaiting()->enqueue(topPatient);
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
                int _pri;
                earlyList.dequeue(next, _pri);
                RandomWaiting()->enqueue(next);
                break;
            case 1:
                
                int _pri;
                lateList.dequeue(next, _pri);
                int penalty = (next->getVT() - next->getPT()) / 2;
                RandomWaiting()->InsertSorted(next, next->getPT() + penalty);
                break;
            case 2:
                
            case 3:
                RandomWaiting()->dequeue(next);
                inTreatementList.enqueue(next, 0);
                RandomWaiting()->dequeue(next);
                inTreatementList.enqueue(next, 0);
                break;
            case 4:
                int _pri;
                inTreatementList.dequeue(next,_pri);
                RandomWaiting()->enqueue(next);
                break;
            case 5:
                int _pri;
                inTreatementList.dequeue(next, _pri);
                finishList.push(next);
                break;
            case 6:
                X_WaitingList.dequeue(next);
                finishList.push(next);
                break;
            case 7:
                int randPatient = rand() % earlyList.getCount();
                earlyList.Reschedule(randPatient);
                break;
            default:
                break;
        }
        }

        M1Queue * RandomWaiting() {
            int randomNumber = (rand() % 101);
            M1Queue * allLists[3] = {&E_WaitingList, &U_WaitingList, &X_WaitingList};
            return allLists[min(randomNumber/33, 2)];
        }

};

