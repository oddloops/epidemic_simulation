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
	double mutationP = decimalDis(gen);
	if (mutationChance <= mutationP)
	{
		std::random_device randomGen;
		std::mt19937 gen(randomGen());
		std::uniform_int_distribution<> mutation(1, 3);
		switch (mutation(gen))
		{
		case 1:
			transmissionRate += 0.2;
			break;
		case 2:
			incubationPeriod -= 1;
			break;
		case 3:
			recoveryPeriod += 2;
			break;
		default:
			break;
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
		if (individual.getDaysInfected() >= recoveryPeriod)
		{
			individual.updateHealthStatus(HealthStatus::Normal);
			individual.updateInfectionStatus(InfectionStatus::Recovered);
		}
		else if (individual.getDaysInfected() >= incubationPeriod)
		{
			std::random_device randomGen;
			std::mt19937 gen(randomGen());
			std::uniform_real_distribution<> decimalDis(0.0, 1.0);
			if (individual.getInfectionStatus() != InfectionStatus::Asymptomatic)
			{
				double infectionSeverity = decimalDis(gen);
				InfectionStatus severity = individual.getInfectionStatus();
				switch (severity)
				{
					case InfectionStatus::CriticalCondition:
						if (infectionSeverity < lethality)
						{
							individual.updateHealthStatus(HealthStatus::Deceased);
							individual.updateInfectionStatus(InfectionStatus::Deceased);
						}
						break;
					case InfectionStatus::MildSymptoms:
						if (infectionSeverity < 0.35)
						{
							individual.updateInfectionStatus(InfectionStatus::SevereSymptoms);
						}
						break;
					case InfectionStatus::SevereSymptoms:
						if (infectionSeverity < 0.28)
						{
							individual.updateInfectionStatus(InfectionStatus::CriticalCondition);
						}
						break;
					default:
						break;
				}
			}
			else {
				std::uniform_int_distribution<> dis(1, 5);
				int infectionSeverity = dis(gen);
				switch (infectionSeverity)
				{
				case 1:
					individual.updateInfectionStatus(InfectionStatus::Symptomatic);
					break;
				case 2:
					individual.updateInfectionStatus(InfectionStatus::MildSymptoms);
					break;
				case 3:
					individual.updateInfectionStatus(InfectionStatus::SevereSymptoms);
					break;
				default:
					break;
				}
			}
		}
	}
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
	return leathality;
}