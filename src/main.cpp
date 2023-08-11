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
    do
    {
        std::cout << "Population Size: ";
        std::cin >> populationSize;
        if (populationSize < 1)
        {
            std::cout << "Please input a valid value > 0" << std::endl;
        }
    } while (populationSize < 1);

    // Simulation Time (in days)
    do
    {
        std::cout << "Simulation Days: ";
        std::cin >> simulationDays;
        if (simulationDays < 1)
        {
            std::cout << "Please input a value > 0" << std::endl;
        }
    } while (simulationDays < 1);

    // Virus attributes
    // Transmission Rate
    do
    {
        std::cout << "Virus transmission rate (0 to 1): ";
        std::cin >> transmissionRate;
        if (transmissionRate < 0 || transmissionRate > 1)
        {
            std::cout << "Please input a value between 0 to 1" << std::endl;
        }
    } while (transmissionRate < 0 || transmissionRate > 1);

    // Incubation Period
    do
    {
        std::cout << "Virus Incubation rate (in days): ";
        std::cin >> incubationPeriod;
        if (incubationPeriod < 0)
        {
            std::cout << "Please input a value >= 0" << std::endl;
        }
    } while (incubationPeriod < 0 );

    // Recovery Period
    do
    {
        std::cout << "Virus Recovery rate (in days): ";
        std::cin >> recoveryPeriod;
        if (recoveryPeriod < 0)
        {
            std::cout << "Please input a value >= 0" << std::endl;
        }
    } while (recoveryPeriod < 0);

    // Mutation Chance
    do
    {
        std::cout << "Virus Mutation Chance (0 to 1): ";
        std::cin >> mutationChance;
        if (mutationChance < 0 || mutationChance > 1)
        {
            std::cout << "Please input a value between 0 to 1" << std::endl;
        }
    } while (mutationChance < 0 || mutationChance > 1);

    // Lethality
    do
    {
        std::cout << "Virus Lethality Rate (0 to 1): ";
        std::cin >> lethality;
        if (lethality < 0 || lethality > 1)
        {
            std::cout << "Please input a value between 0 to 1" << std::endl;
        }
    } while (lethality < 0 || lethality > 1);

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

    for (Individual indi : population)
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
