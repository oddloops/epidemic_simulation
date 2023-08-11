#include <iostream>
#include <cstdlib>
#include <random>

#include "Individual.h"
#include "Enums.h"
#include "Utils.h"
#include "Virus.h"

constexpr int N = 1000;
constexpr int SIMULATION_DAYS = 365 * 100;

int main()
{
    int simulationData[3] = { 0 };

    std::vector<Individual> population;

    // User inputs
    int i, populationSize = N, simulationDays = SIMULATION_DAYS;

    // Virus user inputs
    double transmissionRate = 0, mutationChance = 0, lethality = 0;
    int incubationPeriod = 0, recoveryPeriod = 0;

    // Parse user inputs (Population, Simulation Days then virus information)
    // Population Size
    populationSize = getInputData<int>("Population Size: ", 1, std::numeric_limits<int>::max());

    // Simulation Time (in days)
    simulationDays = getInputData<int>("Simulation duration (in days): ", 1, std::numeric_limits<int>::max());

    // Virus attributes
    // Transmission Rate
    transmissionRate = getInputData<double>("Virus transmission rate (0 to 1): ", 0, 1);

    // Incubation Period
    incubationPeriod = getInputData("Virus Incubation rate (in days): ", 0, std::numeric_limits<int>::max());

    // Recovery Period
    recoveryPeriod = getInputData<int>("Virus Recovery rate (in days): ", 0, std::numeric_limits<int>::max());

    // Mutation Chance
    mutationChance = getInputData<double>("Virus Mutation Chance (0 to 1): ", 0, 1);

    // Lethality
    lethality = getInputData<double>("Virus Lethality Rate (0 to 1): ", 0, 1);

    // Set up population
    for (i = 0; i < populationSize; i++)
    {
        int age = std::rand() % 100;
        population.push_back(Individual(i + 1, age, HealthStatus::Normal, InfectionStatus::Susceptible, 0));
    }

    // Set up virus
    Virus virus(transmissionRate, incubationPeriod, recoveryPeriod, mutationChance, lethality);

    // Set up random number generators
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> individuals(0, populationSize - 1);
    std::uniform_real_distribution<> randomInfection(0, 1);

    // Randomly infect an individual
    int randomInfected = individuals(gen); // Generate a random index
    virus.infect(population[randomInfected]); // Use your Virus.infect() method

    // Begin the simulation loop
    for (i = 0; i <= simulationDays; i++)
    {
        for (int k = 0; k < populationSize; k++) {
            Individual& person = population[k]; // Use reference

            if (person.getHealthStatus() == HealthStatus::Infected)
            {
                virus.severity(person);
                person.incrementInfectionDays();

                if (k - 1 >= 0)
                {
                    virus.spreadTo(population[k - 1]);
                }
                if (k + 1 < populationSize)
                {
                    virus.spreadTo(population[k + 1]);
                }
            }
            else {
                double randomInfectChance = randomInfection(gen);
                if (randomInfectChance < 0.0000002)
                {
                    virus.infect(person);
                }
            }
        }
        //test.mutate();
    }

    for (const Individual& indi : population)
    {
        if (indi.getHealthStatus() == HealthStatus::Infected
            || indi.getHealthStatus() == HealthStatus::Recovered
            || indi.getHealthStatus() == HealthStatus::Deceased)
        {
            simulationData[0]++;
            if (indi.getHealthStatus() == HealthStatus::Recovered)
            {
                simulationData[1]++;
            }
            else if (indi.getHealthStatus() == HealthStatus::Deceased)
            {
                simulationData[2]++;
            }
        }
    }
    std::cout << "Estimated Infected Total: " << simulationData[0] << " / " << N << std::endl;
    std::cout << "Estimated Recovered Total: " << simulationData[1] << " / " << N << std::endl;
    std::cout << "Estimated Deceased Total: " << simulationData[2] << " / " << N << std::endl;
    return 0;
}
