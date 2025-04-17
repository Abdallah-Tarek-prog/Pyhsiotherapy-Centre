#include <iostream>
#include "Scheduler.h"
#include "UIClass.h"
int main()
{
    Scheduler sch;
    UIClass UI;
    
    sch.readInputFile(UI);
    sch.simulate(UI);
}
