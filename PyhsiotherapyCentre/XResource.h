#pragma once
#include"UEResource.h"
#include "GymTool.h"
#include "LinkedQueue.h"
// XResoruce is the same as RoomSource but i renamed it for compatibility
class XResource : public UEResource
{
private:
    int capacity;
    int count;
    LinkedQueue<GymTool*> availDumbbells;
    LinkedQueue<GymTool*> availTreadMills;
    LinkedQueue<GymTool*> availSmith;
public:
    XResource(char Type,int capacity) :UEResource(Type)
    {
        count = 0;
        this->capacity = capacity;
    }
    int getCapacity() const
    {
        return capacity;
    }
    int getCount() const
    {
        return count;
    }
    void InCount()
    {
        count++;
    }
    void DeCount()
    {
        count--;
    }

    bool isToolAvailable(char type) const {
        switch (type) {
            case 'D':
                return !availDumbbells.isEmpty();
            case 'T':
                return !availTreadMills.isEmpty();
            case 'S':
                return !availSmith.isEmpty();
            default:
                return false;
        }
    }
    bool dequeueTool(char type, GymTool*& tool)
    {
        switch(type)
        {
            case 'D':
                return availDumbbells.dequeue(tool);
            case 'T':
                return availTreadMills.dequeue(tool);
            case 'S':
                return availSmith.dequeue(tool);
            default:
                return false;
        }
    }

void enqueueTool(GymTool* tool)
    {
        switch(tool->getType())
        {
            case 'D':
                availDumbbells.enqueue(tool);
                break;
            case 'T':
                availTreadMills.enqueue(tool);
                break;
            case 'S':
                availSmith.enqueue(tool);
                break;
            default:
                break;
        }
    }
    friend std::ostream& operator<<(std::ostream& out,const XResource& r) {
        out << 'R' << r.ID << '[' << r.count << ", " << r.capacity << ']';

        return out;
    }
};

