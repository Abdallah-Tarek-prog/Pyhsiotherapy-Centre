#include <iostream>
#include "Scheduler.h"
#include "UIClass.h"
int main()
{
    Scheduler sch;
    UIClass UI;
    
    sch.readInputFile(UI);

    while(true)
        sch.simulateTimestep(UI);
}
