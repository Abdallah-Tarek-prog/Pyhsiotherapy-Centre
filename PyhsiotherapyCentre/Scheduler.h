#pragma once
#include "Lists.h"
#include "ArrayStack.h"
#include "Patient.h"
#include "ArrayStack.h"
#include "UIClass.h"
#include "U_Therapy.h"
#include "E_Therapy.h"
#include "X_Therapy.h"
#include "UIClass.h"
#include "fstream"

class Scheduler
{
    private:
        int timeStep;
        Lists lists;

        int PCancel;
        int PResc;

        // helper functions for input reading
        
        void populateResouceLists(std::ifstream& inputFile) {
            int EDevices, UDevices, XDevices;

            inputFile >> EDevices >> UDevices >> XDevices;

            while (EDevices--) {
                UEResource* newResource = new UEResource('E');
                lists.E_Deivces.enqueue(newResource);
            }

            while (UDevices--) {
                UEResource* newResource = new UEResource('U');
                lists.U_Deivces.enqueue(newResource);
            }

            while (XDevices--) {
                int capacity;
                inputFile >> capacity;
                XResource* newResource = new XResource('R', capacity);

                lists.X_Rooms.enqueue(newResource);
            }
        }

        void populatePatientList(std::ifstream& inputFile) {
            int patientNumber;

            inputFile >> patientNumber;

            while (patientNumber--) {
                char patientType;
                inputFile >> patientType;

                int PT, VT;
                inputFile >> PT >> VT;

                Patient* newPatient = new Patient(patientType, PT, VT); // This sets Pateints idle by default

                int treatmentNumber;
                inputFile >> treatmentNumber;

                while (treatmentNumber--) {
                    char treatmentType;
                    int treatmentDuration;
                    
                    inputFile >> treatmentType >> treatmentDuration;

                    switch (treatmentType)
                    {
                    case 'U':
                    {
                        U_Therapy* uTreatment = new U_Therapy(treatmentDuration);

                        // TEMP: PHASE 1.2 
                        UEResource* topResource;
                        lists.U_Deivces.peek(topResource);

                        uTreatment->setAssResource(topResource);

                        newPatient->AddTreatment(uTreatment);
                    }
                    case 'E':
                    {
                        E_Therapy* eTreatment = new E_Therapy(treatmentDuration);

                        // TEMP: PHASE 1.2 
                        UEResource* topResource;
                        lists.E_Deivces.peek(topResource);

                        eTreatment->setAssResource(topResource);

                        newPatient->AddTreatment(eTreatment);
                    }
                    case 'X':
                    {
                        X_Therapy* xTreatment = new X_Therapy(treatmentDuration);

                        // TEMP: PHASE 1.2 
                        XResource* topResource;
                        lists.X_Rooms.peek(topResource);

                        xTreatment->setAssResource(topResource);

                        newPatient->AddTreatment(xTreatment);
                    }
                    }
                }

                lists.allPatientsList.enqueue(newPatient);
            }
        }


        
        
    public:
        Scheduler()
        {
            srand(time(0));
            timeStep = 0;
        }

        ~Scheduler()
        {
        }

        bool readInputFile(UIClass& UI) {
            std::string fileName = UI.getFileName("Input");
            std::ifstream inputFile(fileName);

            if (!inputFile) {
                std::cout << fileName << " could not be opened.\n";
                return false;
            }

            populateResouceLists(inputFile);

            inputFile >> PCancel >> PResc;

            populatePatientList(inputFile);

            inputFile.close();

            return true;
        }

        void MoveFromAll(){
            Patient* topPatient;
            
            while(lists.allPatientsList.peek(topPatient)) {
                if (topPatient->getVT() == timeStep) {
                    Patient* temp;
                    lists.allPatientsList.dequeue(temp);
                    
                    if(topPatient->getVT() == topPatient->getPT()){
                        RandomWaiting()->enqueue(topPatient);
                        topPatient->setState(Patient::Wait);
                        continue;
                    }


                    if(topPatient->getVT() > topPatient->getPT()){
                        int penalty = (topPatient->getVT() - topPatient->getPT()) / 2;
                        topPatient->setState(Patient::Late);
                        lists.lateList.enqueue(topPatient, -(topPatient->getVT() + penalty));
                    }else{
                        topPatient->setState(Patient::Early);
                        lists.earlyList.enqueue(topPatient, -(topPatient->getPT()));
                    }
                }
                else {
                    break;
                }
            }
        }
        

      void simulateTimestep()
       {
        
          MoveFromAll();
          timeStep += 1;
          Patient* next;
          M1Queue* rlist;
          int X = rand() % 101;
          int _pri;

          switch (X / 10) {
          case 0:
              if (lists.earlyList.dequeue(next, _pri))
              {
                  RandomWaiting()->enqueue(next);
                  next->setState(Patient::Wait);
              }
              break;
          case 1:

              if (lists.lateList.dequeue(next, _pri))
              {
                  RandomWaiting()->InsertSorted(next, -(next->getPT() + (next->getVT() - next->getPT()) / 2));
                  next->setState(Patient::Wait);
              }
              break;
          case 2:

          case 3:
              rlist = RandomWaiting();
              if (rlist->dequeue(next))
              {
                  lists.inTreatmentList.enqueue(next, 0);
                  next->setState(Patient::Serv);
              }
              if (rlist->dequeue(next))
              { 
                  lists.inTreatmentList.enqueue(next, 0);
                  next->setState(Patient::Serv);

              }
              break;
          case 4:
              if (lists.inTreatmentList.dequeue(next, _pri))
              {
                  RandomWaiting()->enqueue(next);
                  next->setState(Patient::Wait);
              }
              break;
          case 5:
              if (lists.inTreatmentList.dequeue(next, _pri))
              {
                  if (lists.finishedList.push(next))                // The dequeued patient may not 
                      next->setState(Patient::Finished);      //be added in the finish list if there is no space for him
                      
              }
              break;
          case 6: 
             {
                if (lists.X_WaitingList.isEmpty()) break;
                int count = lists.X_WaitingList.getCount(); 
                for (int i = 1; i <= 3 * count; i++) // Loop up to 3*count (Suggest by TA Eng.Eman)
                {
                    if (lists.X_WaitingList.Cancel(rand() % count, next))
                    {
                        lists.finishedList.push(next);
                        next->setState(Patient::Finished);
                        break;
                    }
                }
                break;
            }
          case 7:
              if (!lists.earlyList.getCount()) break;
              lists.earlyList.Reschedule(rand() % lists.earlyList.getCount());
              // Any one in Early list has state early and will still be early
              break;
          default:
              break;
          }


        
        }

        M1Queue * RandomWaiting() {
            int randomNumber = (rand() % 101);
            switch(min(randomNumber/33, 2)){
                case 0:
                    return &lists.E_WaitingList;
                    break;
                case 1:
                    return &lists.U_WaitingList;
                    break;
                case 2:
                    return &lists.X_WaitingList;
                    break;
            }
        }


        void simulate(UIClass& UI) {
            while (true) {
                simulateTimestep();
                UI.printLists(lists, timeStep);
                UI.waitKeyPress();
            }
        }
};

