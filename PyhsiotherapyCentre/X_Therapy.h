#pragma once
#include "Treatment.h"
#include "GymTool.h"


class ToolTreatment {
	int duration;
	char Type; // D T S
	public:
	ToolTreatment(int d, char type) :duration(d), Type(type){}
	int getDuration() const{
		return duration;
	}
	char getType() const{
		return Type;
	}
};

class X_Therapy : public Treatment
{
private:
	LinkedQueue<ToolTreatment*> ToolsRequired; // Max 3
	GymTool* ToolUsed; // Max 3
public:
	X_Therapy();
	// No Representation for these two is required in Phase 1
	bool canAssign(Lists& lists) override;
	void MoveToWait(Scheduler* sch, Patient* p)  override;
	bool getCurrReqTool(ToolTreatment*&); // peek
	void cycleReqTools(); // dequeue and enqueue
	bool removeReqTool(); // dequeue and delete
	void addReqTool(ToolTreatment *); // Used in input phase only.
	void assignTool(GymTool*);
	bool getAssignedTool(GymTool*&);
	bool removeAssignedTool();
};

