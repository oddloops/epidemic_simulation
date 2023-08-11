#include "Virus.h"

Virus::Virus(double rateTransmission, int incubatePeriod, int recoverPeriod, double mutation, double lethalityP)
{
	transmissionRate = rateTransmission;
	incubationPeriod = incubatePeriod;
	recoveryPeriod = recoverPeriod;
	mutationChance = mutation;
	lethality = lethalityP;
}

void Virus::mutate()
{
	std::random_device randomGen;
	std::mt19937 gen(randomGen());
	std::uniform_real_distribution<> decimalDis(0.0, 1.0);
	double mutationP = decimalDis(gen);
	if (mutationChance <= mutationP)
	{
		std::random_device randomGen;
		std::mt19937 gen(randomGen());
		std::uniform_real_distribution<> decimalDis(0.0, 1.0);
		double mutationChance = decimalDis(gen);
		if (mutationChance <= 0.25)
		{
			transmissionRate += 0.2;
		}
		else if (mutationChance <= 0.5)
		{
			incubationPeriod -= 1;
		}
		else if (mutationChance <= 0.75)
		{
			recoveryPeriod += 2;
		}
	}
}

void Virus::spreadTo(Individual& individual)
{
	if (individual.getInfectionStatus() == InfectionStatus::Susceptible)
	{
		double infectionChance = transmissionRate;
		std::random_device randomGen;
		std::mt19937 gen(randomGen());
		std::uniform_real_distribution<> decimalDis(0.0, 1.0);
		double randomChance = decimalDis(gen);
		if (randomChance < infectionChance)
		{
			individual.updateHealthStatus(HealthStatus::Infected);
			individual.updateInfectionStatus(InfectionStatus::Asymptomatic);
		}
	}
}

void Virus::severity(Individual& individual)
{
	if (individual.getHealthStatus() != HealthStatus::Deceased)
	{
		int daysInfected = individual.getDaysInfected();

		if (daysInfected >= recoveryPeriod)
		{
			individual.updateHealthStatus(HealthStatus::Recovered);
			individual.updateInfectionStatus(InfectionStatus::Recovered);
		}
		else if (daysInfected >= incubationPeriod)
		{
			double infectionSeverity = static_cast<double>(daysInfected - incubationPeriod) / (recoveryPeriod - incubationPeriod);

			if (infectionSeverity < 0.25)
			{
				individual.updateInfectionStatus(InfectionStatus::MildSymptoms);
			}
			else if (infectionSeverity < 0.5)
			{
				individual.updateInfectionStatus(InfectionStatus::SevereSymptoms);
			}
			else if (infectionSeverity < 0.75)
			{
				individual.updateInfectionStatus(InfectionStatus::CriticalCondition);
			}
			else
			{
				individual.updateHealthStatus(HealthStatus::Deceased);
				individual.updateInfectionStatus(InfectionStatus::Deceased);
			}
		}
	}
}


void Virus::infect(Individual& individual)
{
	individual.updateHealthStatus(HealthStatus::Infected);
	individual.updateInfectionStatus(InfectionStatus::Asymptomatic);
}

double Virus::getTranmissionRate()
{
	return transmissionRate;
}

int Virus::getIncubationRate()
{
	return incubationPeriod;
}

int Virus::getRecoveryPeriod()
{
	return recoveryPeriod;
}

double Virus::getMutationChance()
{
	return mutationChance;
}

double Virus::getLethality()
{
	return lethality;
}