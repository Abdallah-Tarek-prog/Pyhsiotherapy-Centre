#pragma once
#include "Lists.h"
#include "Patient.h"
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
                        newPatient->AddTreatment(new U_Therapy(treatmentDuration, newPatient));
                    case 'E':
                        newPatient->AddTreatment(new E_Therapy(treatmentDuration, newPatient));
                    case 'X':
                        newPatient->AddTreatment(new X_Therapy(treatmentDuration, newPatient));
                    }
                }
            }
        }


    public:
        Scheduler()
        {
            srand(time(0));
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
                        RandomWaiting(topPatient);
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

        switch (X / 10) {
            case 0:
                lists.earlyList.dequeue(next);
                RandomWaiting(next);
                break;
            case 1:
                lists.lateList.dequeue(next);
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

        UI.printLists(lists, timeStep);
        UI.waitKeyPress();
        
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

