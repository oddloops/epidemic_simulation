#pragma once
#ifndef VIRUS
#define VIRUS

#include <random>
#include "Individual.h"
#include "Enums.h"

class Virus
{
public:
	Virus(double rateTransmission, int incubatePeriod, int recoverPeriod, double mutation, double lethalityP);
	void mutate();
	void spreadTo(Individual& individual);
	void severity(Individual& individual);
	double getTranmissionRate();
	int getIncubationRate();
	int getRecoveryPeriod();
	double getMutationChance();
	double getLethality();

private:
	double transmissionRate;
	int incubationPeriod;
	int recoveryPeriod;
	double mutationChance;
	double lethality;
};

#endif // !VIRUS