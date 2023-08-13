#include "Virus.h"

Virus::Virus(double rateTransmission, int incubatePeriod, int recoverPeriod, double mutation, double lethalityP)
    : transmissionRate(rateTransmission), incubationPeriod(incubatePeriod),
    recoveryPeriod(recoverPeriod), mutationChance(mutation), lethality(lethalityP),
    randomGen(), gen(randomGen()), decimalDis(0.0, 1.0)
{
}

void Virus::mutate()
{
    double mutationP = decimalDis(gen);
    if (mutationChance <= mutationP)
    {
        double mutationChanceValue = decimalDis(gen);
        if (mutationChanceValue <= MUTATION_TRANSMISSION)
        {
            transmissionRate += 0.2;
        }
        else if (mutationChanceValue <= MUTATION_INCUBATION)
        {
            incubationPeriod -= 1;
        }
        else if (mutationChanceValue <= MUTATION_RECOVERY)
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

            double lethalityChance = lethality * infectionSeverity; // Calculate lethality chance based on infection severity

            if (decimalDis(gen) < lethalityChance)
            {
                individual.updateHealthStatus(HealthStatus::Deceased);
                individual.updateInfectionStatus(InfectionStatus::Deceased);
            }
            else if (infectionSeverity < SEVERITY_MILD)
            {
                individual.updateInfectionStatus(InfectionStatus::MildSymptoms);
            }
            else if (infectionSeverity < SEVERITY_SEVERE)
            {
                individual.updateInfectionStatus(InfectionStatus::SevereSymptoms);
            }
            else if (infectionSeverity < SEVERITY_CRITICAL)
            {
                individual.updateInfectionStatus(InfectionStatus::CriticalCondition);
            }
            else // infectionSeverity >= SEVERITY_CRITICAL
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
