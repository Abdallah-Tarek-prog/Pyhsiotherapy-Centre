#pragma once
#include<cctype> // for toupper()
class UEResource
{
	enum Type;
protected:
	 int ID;
	 static int IDGenerator;
	 char Type; // Either 'E' , 'U' or 'X'
public:
	UEResource(char Type)
	{
		this->Type = char(toupper(Type));
		ID = IDGenerator++;
		// We can make ID randomly generated afterwards
		// in this case IDGenerator won't express count of Resources
	}
};
int UEResource::IDGenerator = 0; 
// this is initialization of the 
// static variable

