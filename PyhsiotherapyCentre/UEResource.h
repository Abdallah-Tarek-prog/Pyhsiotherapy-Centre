#pragma once
#include <cctype> // for toupper()
#include <iostream>

class UEResource {
protected:
    int ID;
    static int IDGenerator;
    char Type; // Either 'E', 'U', or 'R'
    int MainTime;   // Maintenance Time
    bool Freefailed;

public:
    UEResource(char Type,int MainTime=-1);

    int getID() const;
    char getType() const;
    int getMainTime()const;
    void setFreeFailed();
    bool getFreeFailed()const;
    friend std::ostream& operator<<(std::ostream& out, const UEResource& r);
};