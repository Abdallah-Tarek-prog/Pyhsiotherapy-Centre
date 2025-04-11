#pragma once
#include <string>
#include <iostream>
#include "Lists.h"

class UIClass
{
private:
	bool silent;
public:
	UIClass();

	std::string getFileName(const std::string& type) const;
	void printLists(Lists& lists, int timestep) const;
	void waitKeyPress() const;
};


UIClass::UIClass() {
	silent = false;
}

std::string UIClass::getFileName(const std::string& type) const{
	std::cout << "Enter " + type + " file name: ";

	std::string fileName;
	cin >> fileName;

	return fileName;
}

void UIClass::printLists(Lists& list, int timestep) const {
	std::cout << "Current Timestep: " << timestep << '\n';

	std::cout << "================ ALL list ================\n";
	std::cout << list.allPatientsList.getCount() << " patients remaining: ";

	list.allPatientsList.print([](Patient* p){
		p->printWithVT();
	}, 10);
	cout << '\n';

	std::cout << "================ Waiting lists ================\n";
	std::cout << list.E_WaitingList.getCount() << " E-therapy patients: ";
	list.E_WaitingList.print();
	cout << '\n';

	std::cout << list.U_WaitingList.getCount() << " U-therapy patients: ";
	list.U_WaitingList.print();
	cout << '\n';


	std::cout << list.X_WaitingList.getCount() << " X-therapy patients: ";
	list.X_WaitingList.print();
	cout << '\n';


	std::cout << "================ Early list ================\n";
	std::cout << list.earlyList.getCount() << " patients: ";
	list.earlyList.print();
	cout << '\n';


	std::cout << "================ Late list ================\n";
	std::cout << list.lateList.getCount() << " patients: ";
	list.lateList.print();
	cout << '\n';


	std::cout << "================ Avail E-Devices ================\n";
	std::cout << list.E_Deivces.getCount() << " Electro device: ";
	list.E_Deivces.print();
	cout << '\n';


	std::cout << "================ Avail U-Devices ================\n";
	std::cout << list.U_Deivces.getCount() << " Ultra device: ";
	list.U_Deivces.print();
	cout << '\n';


	std::cout << "================ Avail X-Devices ================\n";
	std::cout << list.X_Rooms.getCount() << " rooms: ";
	list.X_Rooms.print();
	cout << '\n';


	std::cout << "================ In-treatment List ================\n";
	std::cout << list.inTreatmentList.getCount() << " patients: ";


	list.inTreatmentList.print([](Patient* p) -> void {
		p->printWithTreatment();
	});
	cout << '\n';


	std::cout << "--------------------------------------------------\n";

	std::cout << list.finishedList.getCount() << " finished patients: ";
	list.finishedList.print();
	cout << '\n';

}

void UIClass::waitKeyPress() const {
	std::cout << "Press Enter key to progress timestep...\n";
	std::cin.get();
}