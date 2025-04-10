#include "UIClass.h"
#include <iostream>

UIClass::UIClass() {
	silent = false;
}

std::string UIClass::getFileName(const std::string& type) const{
	std::cout << "Enter " + type + " file name: ";

	std::string fileName;
	cin >> fileName;

	return fileName;
}

void UIClass::printLists(Lists& list) const {

}