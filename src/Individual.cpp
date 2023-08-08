#include "Individual.h"

Individual::Individual(int individualId, int individualAge, HealthStatus hStatus, InfectionStatus iStatus)
{
	id = individualId;
	age = individualAge;
	healthStatus = hStatus;
	infectionStatus = iStatus;
}

// Define getter methods
int Individual::getID() const
{
	return id;
}

int Individual::getAge() const
{
	return age;
}

HealthStatus Individual::getHealthStatus() const
{
	return healthStatus;
}

InfectionStatus Individual::getInfectionStatus() const
{
	return infectionStatus;
}

// Define setter methods
void Individual::updateHealthStatus(HealthStatus newHStatus)
{
	healthStatus = newHStatus;
}

void Individual::updateInfectionStatus(InfectionStatus newIStatus)
{
	infectionStatus = newIStatus;
}