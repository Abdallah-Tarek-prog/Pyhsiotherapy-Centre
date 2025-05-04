#include "X_Therapy.h"
#include "Scheduler.h"


X_Therapy::X_Therapy():Treatment(0, 'X')
{

    ToolUsed = nullptr;

 }

bool X_Therapy::canAssign(Lists& lists)
{
    // Search the available rooms for a room with the needed tools.
    if(lists.X_Rooms.isEmpty()) return false;
    XResource* room;
    LinkedQueue<XResource *> tempQueue;
    bool avail = false;
    while (lists.X_Rooms.peek(room))
    {
        ToolTreatment* currToolTreatment;
        getCurrReqTool(currToolTreatment);
        
        avail = room->isToolAvailable(currToolTreatment->getType());
        if(avail) break;
        // Cycle through rooms
        lists.X_Rooms.dequeue(room); // Remove to check other rooms
        tempQueue.enqueue(room); // Save to return back
    }

    while (tempQueue.dequeue(room))
    {
        lists.X_Rooms.enqueue(room);
    }
    return avail;

}

void X_Therapy::MoveToWait(Scheduler* sch, Patient* p){
    // TODO: Specify Which waiting list should the patient go to.
    // sch->AddToWait_X(p);
    ToolTreatment* currToolTreatment;
    if(!getCurrReqTool(currToolTreatment)) return;
    switch (currToolTreatment->getType())
    {
    case 'D':
        SetDuration(currToolTreatment->getDuration()); // This is inaccurate as the patient may use more than one tool inside the room so they would take more time than anticipated. (This has a non-fatal effect on recovering patients)
        sch->AddToWait_D(p);
        break;
    case 'T':
        SetDuration(currToolTreatment->getDuration()); // This is inaccurate as the patient may use more than one tool inside the room so they would take more time than anticipated. (This has a non-fatal effect on recovering patients)
        sch->AddToWait_T(p);
        break;
    case 'S':
        SetDuration(currToolTreatment->getDuration()); // This is inaccurate as the patient may use more than one tool inside the room so they would take more time than anticipated. (This has a non-fatal effect on recovering patients)
        sch->AddToWait_S(p);
        break;
    
    default:
        break;
    }


}


bool X_Therapy::getCurrReqTool(ToolTreatment*& tool){
    if (X_Therapy::ToolsRequired.isEmpty()) return false;
    X_Therapy::ToolsRequired.peek(tool);
}


bool X_Therapy::removeReqTool(){
    if (X_Therapy::ToolsRequired.isEmpty()) return false;
    ToolTreatment* tool;
    X_Therapy::ToolsRequired.dequeue(tool);
    delete tool;
}




void X_Therapy::addReqTool(ToolTreatment* tool){
    X_Therapy::ToolsRequired.enqueue(tool);
    // SetDuration(GetDuration() + tool->getDuration());
}


void X_Therapy::assignTool(GymTool* tool){
    X_Therapy::ToolUsed = tool;
}


bool X_Therapy::getAssignedTool(GymTool*& tool){
    if(!ToolUsed) return false;
    tool = X_Therapy::ToolUsed;
    return true;
}

bool X_Therapy::removeAssignedTool(){
    if(!ToolUsed) return false;
    X_Therapy::ToolUsed = nullptr;
    return true;
}