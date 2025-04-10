#pragma once
#include <string>
#include "Lists.h"
class UIClass
{
private:
	bool silent;
public:
	UIClass();

	std::string getFileName(const std::string& type) const;
	void printLists(Lists& lists) const;
};

