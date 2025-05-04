#include "UEResource.h"

int UEResource::IDGenerator = 0;

UEResource::UEResource(char Type,int MainTime) {
    this->Type = char(toupper(Type));
    ID = IDGenerator++;
    this->MainTime = MainTime;
    Freefailed = false;
    // We can make ID randomly generated afterwards
    // in that case IDGenerator won't express count of Resources
}

int UEResource::getID() const {
    return ID;
}

char UEResource::getType() const {
    return Type;
}

void UEResource::setFreeFailed()
{
    Freefailed = true;
}

bool UEResource::getFreeFailed()const
{
    return Freefailed;
}

int UEResource::getMainTime()const
{
    return MainTime;
}

std::ostream& operator<<(std::ostream& out, const UEResource& r) {
    out << r.Type << r.ID;
    return out;
}