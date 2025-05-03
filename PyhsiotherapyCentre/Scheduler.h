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
#include <fstream>
#include "statistics.h"
#include<iomanip>
#include <iostream>
// This is the Bonus branch on which we will make bonus

class Scheduler
{
    private:
        statistics stat;
        int timeStep;
        Lists lists;
        int PNum; // Patients total Number
        int PCancel;
        int PResc;
        bool Silent;

        // helper functions for input reading
        
        void populateResouceLists(std::ifstream& inputFile) {
            int EDevices, UDevices, XDevices;

            inputFile >> EDevices >> UDevices >> XDevices;

            while (EDevices--) {
                UEResource* newResource = new UEResource('E');
                lists.E_Devices.enqueue(newResource);
            }

            while (UDevices--) {
                UEResource* newResource = new UEResource('U');
                lists.U_Devices.enqueue(newResource);
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
                if (patientType == 'R')
                    stat.recoveringPatientNum++;
                else if (patientType == 'N')
                    stat.normalPatientNum++;

                int PT, VT;
                inputFile >> PT >> VT;

                Patient* newPatient = new Patient(patientType, PT, VT); // This sets Pateints idle by default

                int treatmentNumber;
                inputFile >> treatmentNumber;

                    char treatmentType;
                while (treatmentNumber--) {
                    int treatmentDuration;
                    
                    inputFile >> treatmentType >> treatmentDuration;

                    switch (treatmentType)
                    {
                    case 'U':
                    {
                        U_Therapy* uTreatment = new U_Therapy(treatmentDuration);
                        newPatient->AddTreatment(uTreatment);
                        break;
                    }
                    case 'E':
                    {
                        E_Therapy* eTreatment = new E_Therapy(treatmentDuration);
                        newPatient->AddTreatment(eTreatment);
                        break;
                    }
                    case 'X':
                    {
                        X_Therapy* xTreatment = new X_Therapy(treatmentDuration);
                        newPatient->AddTreatment(xTreatment);
                        break;
                    }
                    }
                }
                newPatient->setLastTreatment(treatmentType);
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

            stat.normalPatientNum=0;
            stat.recoveringPatientNum=0;

            stat.normalTotalWaitingTime=0;
            stat.recoveringTotalWaitingTime=0;

            stat.normalTotalTreatmentTime=0;
            stat.recoveringTotalTreatmentTime=0;

            stat.numberOfCancel=0;
           stat.numberOfReschedule=0;

            stat.numberOfEarly=0;
            stat.numberOfLate=0;
            stat.totalLatePenalty=0;
                
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


                    if(topPatient->getVT() > topPatient->getPT()){
                        int penalty = (topPatient->getVT() - topPatient->getPT()) / 2;
                        topPatient->setState(Patient::Late);
                        stat.totalLatePenalty += penalty;
                        lists.lateList.enqueue(topPatient, -(topPatient->getVT() + penalty));
                        stat.numberOfLate++;
                        topPatient->setWT(-timeStep);
                    }
                    else if(topPatient->getVT() < topPatient->getPT()){
                        topPatient->setState(Patient::Early);
                        lists.earlyList.enqueue(topPatient, -(topPatient->getPT()));
                        stat.numberOfEarly++;
                        topPatient->setWT(-timeStep);
                    }
                    else{
                        if (topPatient->getPType() == 'R') HandleRP(topPatient);
                        Treatment* t;
                        if (topPatient->getCurrentTreatment(t)) {
                            t->MoveToWait(this, topPatient);
                        }
                        topPatient->setWT(-timeStep);
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
                if (p->getPType() == 'R') HandleRP(p);
                Treatment* t;
                if (p->getCurrentTreatment(t)) {
                    t->MoveToWait(this, p);
                }
                lists.earlyList.dequeue(p, _);
            }
            // Move patients from lateList to the appropriate waiting list.
            int VtPenalty; // VT + Penalty
            while(lists.lateList.peek(p, VtPenalty)) {
                if(-VtPenalty > timeStep)  break; // Negating since priority is negative.
                if (p->getPType() == 'R') HandleRP(p);
                Treatment* t;
                if (p->getCurrentTreatment(t)) {
                    t->MoveToWait(this, p);   
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
                int leaveTime = t->GetST() + t->GetDuration(); // I assume the priority is the same thing as this.
                //int leaveTime = -pri;
                if(leaveTime > timeStep) break;
                UEResource * assignedResource = t->GetAssResource();
                switch(assignedResource->getType())
                {
                    case 'E':
                        lists.E_Devices.enqueue(assignedResource);
                        break;
                    case 'U':
                        lists.U_Devices.enqueue(assignedResource);
                        break;
                    case 'R':
                    {
                        XResource* xRes = (XResource*)assignedResource;
                        if (xRes->getCount() == xRes->getCapacity()) // if the room was removed add it to the available list
                        {
                            lists.X_Rooms.enqueue(xRes);
                        }
                        xRes->DeCount();  // Decrement its count

                        break;
                    }
                    default:
                        break;
                }
                
                p->setTT(p->getTT() + timeStep - t->GetST());
                t->setAssResource(NULL); // For Saftey measures when Debugging

                p->RemoveTreatment();
                if (p->getPType() == 'R') HandleRP(p);

                if(p->getCurrentTreatment(t))
                {
                    t->MoveToWait(this, p);
                }
                else
                {
                    p->setFT(timeStep);
                    p->setState(Patient::Finished);
                    p->setWT(timeStep - p->getTT() + p->getWT());
                    if (p->getPType() == 'R')
                    {
                        stat.recoveringTotalWaitingTime += p->getWT();
                        stat.recoveringTotalTreatmentTime += p->getTT();
                    }
                    else if (p->getPType() == 'N')
                    {
                        stat.normalTotalWaitingTime += p->getWT();
                        stat.normalTotalTreatmentTime += p->getTT();
                    }

                    lists.finishedList.push(p);
                }

                lists.inTreatmentList.dequeue(p, pri);
            }
        }

        void ReschSimulation()
        {
            if (lists.earlyList.getCount() != 0)    
            {
                int ProbResch = rand() % 101;
                if (ProbResch < PResc) {
                    int ranNum = rand();
                    ranNum %= lists.earlyList.getCount();
                    if(lists.earlyList.Reschedule(ranNum))
                        stat.numberOfReschedule++;

                }
            }
        }
        void CancSimulation()
        {
            if (lists.X_WaitingList.getCount() != 0)
            {
                int ProbCancel = rand() % 101;
                if (ProbCancel < PCancel) {
                    int ranNum = rand();
                    Patient* pat;
                    ranNum %= lists.X_WaitingList.getCount();
                    if (lists.X_WaitingList.Cancel(ranNum, pat))
                    {
                        pat->setState(Patient::Finished);
                        pat->setCancelled(true);
                        // Handling the Times of the cancelled patient
                        pat->setFT(timeStep);
                        pat->setWT(timeStep - pat->getTT() + pat->getWT());
                        // Treatment Time should be as it is 
                        if(pat->getPType()=='R')
                        {
                            stat.recoveringTotalWaitingTime += pat->getWT();
                            stat.recoveringTotalTreatmentTime += pat->getTT();
                        }
                        else if(pat->getPType()=='N')
                        {
                            stat.normalTotalWaitingTime += pat->getWT();
                            stat.normalTotalTreatmentTime += pat->getTT();
                        }

                        stat.numberOfCancel++;
                        lists.finishedList.push(pat);
                    }
                }
            }
        }

      void simulateTimestep()
       {
        
            timeStep += 1;
            checkout(); // Returning back the devices after finishing should be done at first !!! 
            MoveFromAll();
            ReschSimulation();  // For handling rescheduling in early list
            dispatch();
            CancSimulation();   // For handling cancelling 
            Assign_E();     
            Assign_U();
            Assign_X();
        
       }

      void AddToWait_E(Patient* p) {
          if (p->getState() == Patient::Late) {
              int penalty = (p->getVT() - p->getPT()) / 2;
              lists.E_WaitingList.InsertSorted(p, -(p->getPT() + penalty));
	            p->setState(Patient::Wait);
              return;
          }
          p->setState(Patient::Wait);
          lists.E_WaitingList.enqueue(p);
      }
      void AddToWait_U(Patient* p) {
          if (p->getState() == Patient::Late) {
              int penalty = (p->getVT() - p->getPT()) / 2;
              lists.U_WaitingList.InsertSorted(p, -(p->getPT() + penalty));
              p->setState(Patient::Wait);
              return;
          }
          p->setState(Patient::Wait);
          lists.U_WaitingList.enqueue(p);
      }
      void AddToWait_X(Patient* p) {
          if (p->getState() == Patient::Late) {
              int penalty = (p->getVT() - p->getPT()) / 2;
              lists.X_WaitingList.InsertSorted(p, -(p->getPT() + penalty));
              p->setState(Patient::Wait);
              return;
          }
          p->setState(Patient::Wait);
          lists.X_WaitingList.enqueue(p);
      }

      void Assign_E() {
          while (!lists.E_WaitingList.isEmpty()) {
              Patient* patient;
              lists.E_WaitingList.peek(patient);

              Treatment* eTreatment;
              patient->getCurrentTreatment(eTreatment);

              if (!eTreatment->canAssign(lists))
                  return;

              lists.E_WaitingList.dequeue(patient);

              UEResource* resource;
              lists.E_Devices.dequeue(resource);

              eTreatment->setAssResource(resource);
              eTreatment->setST(timeStep);

              lists.inTreatmentList.enqueue(patient, -(timeStep + eTreatment->GetDuration()));
              patient->setState(Patient::Serv);
          }
      }

      void Assign_U() {
          while (!lists.U_WaitingList.isEmpty()) {
              Patient* patient;
              lists.U_WaitingList.peek(patient);

              Treatment* uTreatment;
              patient->getCurrentTreatment(uTreatment);

              if (!uTreatment->canAssign(lists))
                  return;

              lists.U_WaitingList.dequeue(patient);

              UEResource* resource;
              lists.U_Devices.dequeue(resource);

              uTreatment->setAssResource(resource);
              uTreatment->setST(timeStep);

              lists.inTreatmentList.enqueue(patient, -(timeStep + uTreatment->GetDuration()));
              patient->setState(Patient::Serv);
          }
      }

      void Assign_X() {
          while (!lists.X_WaitingList.isEmpty()) {
              Patient* patient;
              lists.X_WaitingList.peek(patient);
                  
              Treatment* xTreatment;
              patient->getCurrentTreatment(xTreatment);

               if (!xTreatment->canAssign(lists))
                   return;

              lists.X_WaitingList.dequeue(patient);

              XResource*  resource;
              lists.X_Rooms.peek(resource);

              resource->InCount();

              if (resource->getCount() == resource->getCapacity()) {
                  lists.X_Rooms.dequeue(resource);
              }

              xTreatment->setAssResource(resource);
              xTreatment->setST(timeStep);

              lists.inTreatmentList.enqueue(patient, -(timeStep + xTreatment->GetDuration()));
              patient->setState(Patient::Serv);
          }
      }


      void HandleRP(Patient* p) {       // Every time we want to insert RP into a waiting this is called
          if (p->getPType() != 'R')
              return;
          
          // Priority Queue to store the treatments based on their TL
          priQueue<Treatment*> newOrderTreatments;

          Treatment* t;
          while (p->getCurrentTreatment(t)) {
              p->RemoveTreatment();
              int TL;

              // Getting the TL based on the treatment type
              switch (t->GetType())
              {
              case 'E':
                  TL = lists.E_WaitingList.calculateTL();
                  break;
              case 'U':
                  TL = lists.U_WaitingList.calculateTL();
                  break;
              case 'X':
                  TL = lists.X_WaitingList.calculateTL();
                  break;
              default:
                  TL = 0;
                  break;
              };

              newOrderTreatments.enqueue(t, -TL); 
          }

          int _;
          while (newOrderTreatments.dequeue(t, _)) {
              p->AddTreatment(t);
          }
      }

      void simulate(UIClass& UI) {
          readInputFile(UI);
          Silent = UI.GetState();
          while (lists.finishedList.getCount() != PNum) {
              simulateTimestep();
              if (!Silent) {
                  UI.printLists(lists, timeStep);
                  UI.waitKeyPress();
              }
          }
          if (!Silent)
          {
             UI.print("----------------------------  Simulation Ended press @ to exit  ----------------------------\n");
             int dummy;
          do
             {
                    dummy = _getch();
             } while (dummy != '@');
          }
            PrintOutputFile(UI);
            if (!Silent) {
                UI.print("Output File is created\n");
            }
            else
                UI.print("Silent Mode, Simulation ends, Output file created\n");
        }
      
      void PrintOutputFile(UIClass& UI)
      {
          string filename = UI.getFileName("Output");
          ofstream Outfile(filename + ".txt");
          if (!Outfile)
          {
              cout << "Error occured Output File wasn't created\n";
          }
          else
          {
              Patient* pat;
              Outfile << left << setw(6) << "PID"
                  << left << setw(10) << "PType"
                  << left << setw(6) << "PT"
                  << left << setw(6) << "VT"
                  << left << setw(6) << "FT"
                  << left << setw(6) << "WT"
                  << left << setw(6) << "TT"
                  << left << setw(10) << "Cancel"
                  << left << setw(8) << "Resc" << "\n";

              while (lists.finishedList.pop(pat))
              {
                  Outfile << left << setw(6) << ("P" + to_string(pat->getID()))
                      << left << setw(10) << pat->getPType()
                      << left << setw(6) << pat->getPT()
                      << left << setw(6) << pat->getVT()
                      << left << setw(6) << pat->getFT()
                      << left << setw(6) << pat->getWT()
                      << left << setw(6) << pat->getTT()
                      << left << setw(10) << (pat->isCancelled() ? "T" : "F")
                      << left << setw(8) << (pat->getRescheduled() > 0 ? "T" : "F") << "\n";
              }

              double TotalWaitingTime = stat.normalTotalWaitingTime + stat.recoveringTotalWaitingTime;
              double TotalTreatmentTime = stat.normalTotalTreatmentTime + stat.recoveringTotalTreatmentTime;
              double AvgLatePenalty = 0;
              if ((PNum - stat.numberOfEarly) > 0)
              {
                  AvgLatePenalty = static_cast<double>(stat.totalLatePenalty) / (PNum - stat.numberOfEarly);
              }

              double AvgTotalTreatmentTimeN = stat.normalPatientNum > 0? (double)stat.normalTotalTreatmentTime / stat.normalPatientNum: 0;
              double AvgTotalWaitTimeN = stat.normalPatientNum > 0? (double)stat.normalTotalWaitingTime / stat.normalPatientNum: 0;
              double AvgTotalTreatmentTimeR = stat.recoveringPatientNum > 0? (double)stat.recoveringTotalTreatmentTime / stat.recoveringPatientNum: 0;
              double AvgTotalWaitTimeR = stat.recoveringPatientNum > 0? (double)stat.recoveringTotalWaitingTime / stat.recoveringPatientNum: 0;
              Outfile << "Total number of timesteps = " << timeStep << endl
                  << "Total number of all, N, and R patients = " << PNum << " , " << stat.normalPatientNum << " , " << stat.recoveringPatientNum << endl
                  << "Average total waiting time for all, N, and R patients = " << fixed << setprecision(2)
                  << TotalWaitingTime / PNum << " , " << AvgTotalWaitTimeN
                  << " , " << AvgTotalWaitTimeR << endl
                  << "Average total treatment time for all, N, and R patients = "
                  << TotalTreatmentTime / PNum << " , " << AvgTotalTreatmentTimeN
                  << " , " << AvgTotalTreatmentTimeR << endl
                  << "Percentage of patients of an accepted cancellation (%) = "
                  << (double)stat.numberOfCancel * 100 / PNum << " %\n"
                  << "Percentage of patients of an accepted rescheduling(%) = "
                  << (double)stat.numberOfReschedule * 100 / PNum << " %\n"
                  << "Percentage of early patients(%) = "
                  << (double)stat.numberOfEarly * 100 / PNum << " %\n"
                  << "Percentage of late patients (%) = "
                  << (double)(stat.numberOfLate) * 100 / PNum << " %\n"
                  << "Average late penalty = " << AvgLatePenalty << " timestep(s)";
          }
      }
};


