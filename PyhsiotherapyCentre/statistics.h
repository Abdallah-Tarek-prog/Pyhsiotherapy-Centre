#pragma once
struct statistics
{
	int normalPatientNum;
	int recoveringPatientNum;

	int normalTotalWaitingTime;
	int recoveringTotalWaitingTime;

	int normalTotalTreatmentTime;
	int recoveringTotalTreatmentTime;

	int numberOfCancel;
	int numberOfReschedule;

	int numberOfEarly;
	int totalLatePenalty;

};

