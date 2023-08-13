#ifndef VIRUS_H
#define VIRUS_H

#include <random>
#include "Individual.h"

class Virus
{
public:
    Virus(double rateTransmission, int incubatePeriod, int recoverPeriod, double mutation, double lethalityP);
    void mutate();
    void spreadTo(Individual& individual);
    void severity(Individual& individual);
    void infect(Individual& individual);

    // Getters
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

    std::random_device randomGen;
    std::mt19937 gen;
    std::uniform_real_distribution<> decimalDis;

    // Mutation Constants
    static constexpr double MUTATION_TRANSMISSION = 0.25;
    static constexpr double MUTATION_INCUBATION = 0.5;
    static constexpr double MUTATION_RECOVERY = 0.75;

    // Severity Constants
    static constexpr double SEVERITY_MILD = 0.25;
    static constexpr double SEVERITY_SEVERE = 0.5;
    static constexpr double SEVERITY_CRITICAL = 0.75;
};

#endif // VIRUS_H