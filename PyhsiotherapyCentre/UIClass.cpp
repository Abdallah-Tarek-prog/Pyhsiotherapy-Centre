#include "UIClass.h"
#include <cctype> // For toupper

UIClass::UIClass() {
    silent = false;
}

std::string UIClass::getFileName(const std::string& type) const {
    std::cout << "Enter " + type + " file name: ";

    std::string fileName;
    std::cin >> fileName;
    std::cin.ignore();

    return fileName;
}

void UIClass::printLists(Lists& list, int timestep) const {
    std::cout << "Current Timestep: " << timestep << '\n';

    std::cout << "================ ALL list ================\n";
    std::cout << list.allPatientsList.getCount() << " patients remaining: ";
    list.allPatientsList.print(10);
    std::cout << '\n';

    std::cout << "================ Waiting lists ================\n";
    std::cout << list.E_WaitingList.getCount() << " E-therapy patients: ";
    list.E_WaitingList.print();
    std::cout << '\n';

    std::cout << list.U_WaitingList.getCount() << " U-therapy patients: ";
    list.U_WaitingList.print();
    std::cout << '\n';

    std::cout << list.X_WaitingList.getCount() << " X-therapy patients: ";
    list.X_WaitingList.print();
    std::cout << '\n';

    std::cout << "================ Early list ================\n";
    std::cout << list.earlyList.getCount() << " patients: ";
    list.earlyList.print();
    std::cout << '\n';

    std::cout << "================ Late list ================\n";
    std::cout << list.lateList.getCount() << " patients: ";
    list.lateList.print();
    std::cout << '\n';

    std::cout << "================ Avail E-Devices ================\n";
    std::cout << list.E_Devices.getCount() << " Electro device: ";
    list.E_Devices.print();
    std::cout << '\n';

    std::cout << "================ Avail U-Devices ================\n";
    std::cout << list.U_Devices.getCount() << " Ultra device: ";
    list.U_Devices.print();
    std::cout << '\n';

    std::cout << "================ Avail X-Devices ================\n";
    std::cout << list.X_Rooms.getCount() << " rooms: ";
    list.X_Rooms.print();
    std::cout << '\n';

    std::cout << "================ Failed Devices ================\n";
    std::cout << list.FailedDevices.getCount() << " Failed Devices: ";
    list.FailedDevices.print();
    std::cout << '\n';

    std::cout << "================ In-treatment List ================\n";
    std::cout << list.inTreatmentList.getCount() << " patients: ";
    list.inTreatmentList.print();
    std::cout << '\n';

    std::cout << "================ Interrupted U_Patient List ================\n";
    std::cout << list.U_interruptedPatients.getCount() << " patients: ";
    list.U_interruptedPatients.print();
    std::cout << '\n';

    std::cout << "================ Interrupted E_Patient List ================\n";
    std::cout << list.E_interruptedPatients.getCount() << " patients: ";
    list.E_interruptedPatients.print();
    std::cout << '\n';

    std::cout << "--------------------------------------------------\n";

    std::cout << list.finishedList.getCount() << " finished patients: ";
    list.finishedList.print();
    std::cout << "\n";
}

void UIClass::waitKeyPress() const {
    std::cout << "Press Enter key to progress timestep...\n\n";
    int dummy = _getch();
}

void UIClass::print(const std::string& message) const {
    std::cout << message;
}

bool UIClass::GetState() {
    char ch;
    std::cout << "----------------------------------\n";
    std::cout << "Enter 'S' for Silent mode\n"
        << "      'I' for Interactive mode\n";
    do {
        std::cin >> ch;
        ch = toupper(ch);
    } while (ch != 'S' && ch != 'I');
    std::cout << "----------------------------------\n";
    return ch == 'S'; // Return true for Silent, false for Interactive
}