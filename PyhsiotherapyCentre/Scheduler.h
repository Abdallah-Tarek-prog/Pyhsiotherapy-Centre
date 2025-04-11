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

                Patient* newPatient = new Patient(patientType, PT, VT);

                int treatmentNumber;
                inputFile >> treatmentNumber;

                while (treatmentNumber--) {
                    char treatmentType;
                    int treatmentDuration;
                    
                    inputFile >> treatmentType >> treatmentDuration;

                    switch (treatmentType)
                    {
                    case 'U':
                        newPatient->AddTreatment(new U_Therapy(treatmentDuration));
                    case 'E':
                        newPatient->AddTreatment(new E_Therapy(treatmentDuration));
                    case 'X':
                        newPatient->AddTreatment(new X_Therapy(treatmentDuration));
                    }
                }
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
                        continue;
                    }


                    if(topPatient->getVT() > topPatient->getPT()){
                        int penalty = (topPatient->getVT() - topPatient->getPT()) / 2;
                        lists.lateList.enqueue(topPatient, topPatient->getVT() + penalty);
                    }else{
                        lists.earlyList.enqueue(topPatient, topPatient->getPT());
                    }
                }
            }
        }
        

      void simulateTimestep(UIClass& UI)
       {    
        MoveFromAll();
        
        Patient * next;

        int X = rand() % 101;
        int _pri;

        switch (X / 10) {
            case 0:
                lists.earlyList.dequeue(next, _pri);
                RandomWaiting()->enqueue(next);
                break;
            case 1:
                
                lists.lateList.dequeue(next, _pri);
                RandomWaiting()->InsertSorted(next, next->getPT() + (next->getVT() - next->getPT()) / 2);
                break;
            case 2:
                
            case 3:
                RandomWaiting()->dequeue(next);
                lists.inTreatmentList.enqueue(next, 0);
                RandomWaiting()->dequeue(next);
                lists.inTreatmentList.enqueue(next, 0);
                break;
            case 4:
                lists.inTreatmentList.dequeue(next,_pri);
                RandomWaiting()->enqueue(next);
                break;
            case 5:
                lists.inTreatmentList.dequeue(next, _pri);
                lists.finishedList.push(next);
                break;
            case 6:
                lists.X_WaitingList.dequeue(next);
                lists.finishedList.push(next);
                break;
            case 7:
                lists.earlyList.Reschedule(rand() % lists.earlyList.getCount());
                break;
            default:
                break;
        }

        UI.printLists(lists, timeStep);
        UI.waitKeyPress();
        
        }

        M1Queue * RandomWaiting() {
            int randomNumber = (rand() % 101);
            M1Queue * allLists[3] = {&lists.E_WaitingList, &lists.U_WaitingList, &lists.X_WaitingList};
            return allLists[min(randomNumber/33, 2)];
        }

};

