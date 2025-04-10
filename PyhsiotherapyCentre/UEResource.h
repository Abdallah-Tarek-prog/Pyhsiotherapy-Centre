#pragma once
#include<cctype> // for toupper()
#include <iostream>
class UEResource
{
	enum Type;
protected:
	 int ID;
	 static int IDGenerator;
	 char Type; // Either 'E' , 'U' or 'R'
public:
	UEResource(char Type)
	{
		this->Type = char(toupper(Type));
		ID = IDGenerator++;
		// We can make ID randomly generated afterwards
		// in this case IDGenerator won't express count of Resources
	}

	int getID() const { return ID; }
	int getType() const { return Type; }


	friend std::ostream& operator<<(std::ostream& out, UEResource& r) {
		out << r.ID;

		return out;
	}
};
int UEResource::IDGenerator = 0;
// this is initialization of the 
// static variable

