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
#include "statistics.h"
#include<iomanip>
#include <iostream>

class Scheduler
{
    private:
        statistics stat;
        int timeStep;
        Lists lists;
        int PNum; // Patients total Number
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
            PNum = patientNumber;

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
                        newPatient->AddTreatment(uTreatment);
                    }
                    case 'E':
                    {
                        E_Therapy* eTreatment = new E_Therapy(treatmentDuration);
                        newPatient->AddTreatment(eTreatment);

                    }
                    case 'X':
                    {
                        X_Therapy* xTreatment = new X_Therapy(treatmentDuration);
                        newPatient->AddTreatment(xTreatment);
                    }
                    }
                }

                lists.allPatientsList.enqueue(newPatient);
            }
        }

        bool readInputFile(UIClass& UI) {
            std::string fileName = UI.getFileName("Input");
            std::ifstream inputFile(fileName);

            if (!inputFile) {
                std::cout << fileName << " could not be opened.\n";
                exit(1);        // non-zero value indicates error state
                return false;
            }

            populateResouceLists(inputFile);

            inputFile >> PCancel >> PResc;

            populatePatientList(inputFile);

            inputFile.close();

            return true;
        }

        
        
    public:
        Scheduler()
        {
            srand(time(0));
            timeStep = -1;
        }

        ~Scheduler()
        {
        }

        

        void MoveFromAll(){
            Patient* topPatient;
            
            while(lists.allPatientsList.peek(topPatient)) {
                if (topPatient->getVT() == timeStep) {
                    Patient* temp;
                    lists.allPatientsList.dequeue(temp);
                    

                    // Will handle this in the simulateTimestep function
                    //
                    // if(topPatient->getVT() == topPatient->getPT()){
                    //     RandomWaiting()->enqueue(topPatient);
                    //     topPatient->setState(Patient::Wait);
                    //     continue;
                    // }


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
        

        void dispatch(){
            Patient* p;
            int _;
            // Move patients from earlyList to the appropriate waiting list.
            while(lists.earlyList.peek(p, _)) {
                if(p->getPT() > timeStep)  break;
                Treatment* t;
                if (p->getCurrentTreatment(t)) {
                    t->MoveToWait(this);
                }
                lists.earlyList.dequeue(p, _);
            }
            // Move patients from lateList to the appropriate waiting list.
            int VtPenalty; // VT + Penalty
            while(lists.lateList.peek(p, VtPenalty)) {
                if(-VtPenalty > timeStep)  break; // Negating since priority is negative.
                Treatment* t;
                if (p->getCurrentTreatment(t)) {
                    t->MoveToWait(this);    // TODO I need to be able to tell it that the patient came from the late list so that hes put in the waiting list according to PT + Penalty. For now, I will rely on the state.
                }
                lists.lateList.dequeue(p, _);
            }
        }


        void checkout(){
            Patient* p;
            int pri;
            // Move patients from inTreatmentList to the appropriate waiting list.
            while(lists.inTreatmentList.peek(p, pri)) {
                Treatment* t;
                p->getCurrentTreatment(t);
                //int leaveTime = t->GetST() + t->GetDuration(); I assume the priority is the same thing as this.
                int leaveTime = -pri;
                if(pri > timeStep) break;
                UEResource * assignedResource = t->GetAssResource();
                switch(assignedResource->getType())
                {
                    case 'E':
                        lists.E_Deivces.enqueue(assignedResource);
                        break;
                    case 'U':
                        lists.U_Deivces.enqueue(assignedResource);
                        break;
                    case 'X':
                        XResource * xRes = (XResource * )assignedResource; // FIXME I don't like this, Eman/Marwa will hate it.
                        if (xRes->getCount() < xRes->getCapacity())
                        {
                            lists.X_Rooms.enqueue(xRes);
                        }
                        
                        break;
                    default:
                        break;
                }
                p->RemoveTreatment();
                if(p->getCurrentTreatment(t)){
                    t->MoveToWait(this);
                }else{
                    p->setFT(timeStep);
                    p->setState(Patient::Finished);
                }

                lists.inTreatmentList.dequeue(p, pri);
            }
        }



      void simulateTimestep()
       {
        
            timeStep += 1;
            MoveFromAll();
            dispatch();
            Assign_E(); 
            Assign_U();
            Assign_X();
            checkout();
        
       }

      void AddToWait_E(Patient* p) {
          lists.E_WaitingList.enqueue(p);
      }
      void AddToWait_U(Patient* p) {
          lists.U_WaitingList.enqueue(p);
      }
      void AddToWait_X(Patient* p) {
          lists.X_WaitingList.enqueue(p);
      }

      void Assign_E() {
          while (!lists.E_WaitingList.isEmpty() && !lists.E_Deivces.isEmpty()) {
              Patient* patient;
              lists.E_WaitingList.dequeue(patient);

              UEResource* resource;
              lists.E_Deivces.dequeue(resource);

              Treatment* eTreatment;
              patient->getCurrentTreatment(eTreatment);

              eTreatment->setAssResource(resource);

              lists.inTreatmentList.enqueue(patient, timeStep + eTreatment->GetDuration());
          }
      }

      void Assign_U() {
          while (!lists.U_WaitingList.isEmpty() && !lists.U_Deivces.isEmpty()) {
              Patient* patient;
              lists.U_WaitingList.dequeue(patient);

              UEResource* resource;
              lists.U_Deivces.dequeue(resource);

              Treatment* uTreatment;
              patient->getCurrentTreatment(uTreatment);

              uTreatment->setAssResource(resource);

              lists.inTreatmentList.enqueue(patient, timeStep + uTreatment->GetDuration());
          }
      }

      void Assign_X() {
          while (!lists.X_WaitingList.isEmpty() && !lists.X_Rooms.isEmpty()) {
              Patient* patient;
              lists.X_WaitingList.dequeue(patient);

              XResource*  resource;
              lists.X_Rooms.peek(resource);

              resource->InCount();

              if (resource->getCount() == resource->getCapacity()) {
                  lists.X_Rooms.dequeue(resource);
              }

              Treatment* xTreatment;
              patient->getCurrentTreatment(xTreatment);

              xTreatment->setAssResource(resource);

              lists.inTreatmentList.enqueue(patient, timeStep + xTreatment->GetDuration());
          }
      }

      void HandleRP(Patient* p) {
          if (p->getPType() != 'R')
              return;

          int minTL = INT_MAX;
          Treatment* chosenTreatment;
          M1Queue* chosenList ;

          LinkedQueue<Treatment*> tempList;
          Treatment* tempTreatment;

          while (p->getCurrentTreatment(tempTreatment)) {
              p->RemoveTreatment();

              switch (tempTreatment->GetType())
              {
              case 'U':
              {
                  int currTL = lists.U_WaitingList.calculateTL();
                  minTL = min(minTL, currTL);

                  if (currTL == minTL)
                  {
                      chosenList = &(lists.U_WaitingList);
                      chosenTreatment = tempTreatment;
                  }

                  break;
              }

              case 'X':
              {
                  int currTL = lists.X_WaitingList.calculateTL();
                  minTL = min(minTL, currTL);

                  if (currTL == minTL)
                  {
                      chosenList = &(lists.X_WaitingList);
                      chosenTreatment = tempTreatment;
                  }

                  break;
              }
              case 'E':
              {
                  int currTL = lists.E_WaitingList.calculateTL();
                  minTL = min(minTL, currTL);

                  if (currTL == minTL)
                  {
                      chosenList = &(lists.E_WaitingList);
                      chosenTreatment = tempTreatment;
                  }

                  break;
              }

              }

              tempList.enqueue(tempTreatment);

          }

          p->AddTreatment(chosenTreatment);

          while (tempList.dequeue(tempTreatment)) {
              if (tempTreatment == chosenTreatment)
                  continue;

              p->AddTreatment(tempTreatment);
          }

          chosenList->enqueue(p);
      }

        void simulate(UIClass& UI) {
            readInputFile(UI);
            while (lists.finishedList.getCount()!=PNum) {
                simulateTimestep();
                UI.printLists(lists, timeStep);
                UI.waitKeyPress();
            }
            cout << "----------------------------  Simulation Ended press @ to exit  ----------------------------";
            int dummy;
            do 
            {  dummy = _getch(); }
            while (dummy!='@');
            PrintOutputFile();
            cout << "Output file is created\n";
        }

        void PrintOutputFile()
        {
            ofstream Outfile("Output File");
            if (!Outfile)
            {
                cout << "Error occured Output File wasn't created\n";
            }
            else
            {
                Patient* pat;
                cout << "PID PType PT VT FT WT TT Cancel Resc\n";
                while (lists.finishedList.pop(pat))
                {
                    cout << "P" << pat->getID() << "  "
                        << "PType" << pat->getPType() << "  "
                        << pat->getPT() << "  "
                        << pat->getVT() << "  "
                        << pat->getFT() << "   "
                        << pat->getWT() << "   "
                        << pat->getTT() << "   ";

                    if (pat->isCancelled())
                        cout << "T    ";
                    else cout << "F     ";

                    if (pat->isRescheduled())
                        cout << "T    ";
                    else cout << "F     ";
                    cout << endl;
                }
                double TotalWaitingTime = stat.normalTotalWaitingTime + stat.recoveringTotalWaitingTime;
                double TotalTreatmentTime = stat.normalTotalTreatmentTime + stat.recoveringTotalTreatmentTime;

                cout << "Total number of timesteps = " << timeStep << endl // Considering timestep is the last one
                    << "Total number of all, N, and R patients = " << PNum << " , " << stat.normalPatientNum << " , " << stat.recoveringPatientNum << endl
                    << "Average total waiting time for all, N, and R patients = " << fixed << setprecision(2) << TotalWaitingTime / PNum << " , " << (double)stat.normalTotalWaitingTime / stat.normalPatientNum << " , " << (double)stat.recoveringTotalWaitingTime / stat.recoveringPatientNum << endl
                    << "Average total treatment time for all, N, and R patients = " << TotalTreatmentTime / PNum << " , " << (double)stat.normalTotalTreatmentTime / stat.normalPatientNum << " , " << (double)stat.recoveringTotalTreatmentTime / stat.recoveringPatientNum << endl
                    << "Percentage of patients of an accepted cancellation (%) = " << (double)stat.numberOfCancel * 100 / PNum << " %\n"
                    << "Percentage of patients of an accepted rescheduling(%) = " << (double)stat.numberOfReschedule * 100 / PNum << " %\n"
                    << "Percentage of early patients(%) = " << (double)stat.numberOfEarly * 100 / PNum<<" %\n"
                    <<"Percentage of late patients (%) = " <<(double)(PNum-stat.numberOfEarly)*100/PNum << " %\n"
                    <<"Average late penalty = "<<(double)(stat.totalLatePenalty)/(PNum-stat.numberOfEarly)<<"timestep(s)";
            }
        }
};

