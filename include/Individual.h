#pragma once
#ifndef INDIVIDUAL
#define INDIVIDUAL

#include "Enums.h"
#include "Utils.h"

class Individual
{
public:
	Individual(int id, int age, HealthStatus hStatus, InfectionStatus iStatus, int infectionDays);

	// Implicit declaration of getter methods
	int getID() const;
	int getAge() const;
	int getDaysInfected() const;
	HealthStatus getHealthStatus() const;
	InfectionStatus getInfectionStatus() const;

	// Implicit declaration of setter methods
	void updateHealthStatus(HealthStatus newHStatus);
	void updateInfectionStatus(InfectionStatus newIStatus);
	void incrementInfectionDays();

private:
	int id;
	int age;
	HealthStatus healthStatus;
	InfectionStatus infectionStatus;
	int daysInfected;
};

#endif