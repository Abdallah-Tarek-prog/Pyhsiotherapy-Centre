#pragma once

class GymTool {
	int ID;
	static int IDGenerator;
	char Type; // T: TreadMill, D: Dumbbells, S: Smith Machine 
public:
	GymTool(char type);
	char getType() const;
	int getID() const;
};
