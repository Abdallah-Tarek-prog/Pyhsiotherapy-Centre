#include "UEResource.h"

int UEResource::IDGenerator = 0;

UEResource::UEResource(char Type) {
    this->Type = char(toupper(Type));
    ID = IDGenerator++;
    // We can make ID randomly generated afterwards
    // in that case IDGenerator won't express count of Resources
}

int UEResource::getID() const {
    return ID;
}

char UEResource::getType() const {
    return Type;
}

std::ostream& operator<<(std::ostream& out, const UEResource& r) {
    out << r.ID;
    return out;
}