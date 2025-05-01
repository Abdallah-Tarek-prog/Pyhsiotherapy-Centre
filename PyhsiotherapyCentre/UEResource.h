#pragma once
#include <cctype> // for toupper()
#include <iostream>

class UEResource {
protected:
    int ID;
    static int IDGenerator;
    char Type; // Either 'E', 'U', or 'R'

public:
    UEResource(char Type);

    int getID() const;
    char getType() const;

    friend std::ostream& operator<<(std::ostream& out, const UEResource& r);
};