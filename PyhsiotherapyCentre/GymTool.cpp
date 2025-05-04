#include <cctype>
#include "GymTool.h"
int GymTool::IDGenerator = 0;

GymTool::GymTool(char type) {
	this->Type = char(toupper(type));
	ID = IDGenerator++;
}

char GymTool::getType() const {
	return Type;
}

int GymTool::getID() const {
	return ID;
}