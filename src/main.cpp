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
    int i;
    for (i = 0; i < N; i++)
    {
        int age = std::rand() % 100;
        population.push_back(Individual(i + 1, age, HealthStatus::Normal, InfectionStatus::Susceptible, 0));
    }

    Virus test(0.31, 3, 8, 0.02, 0.11);

    // Randomly infect an individual
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> individuals(0, N - 1);
    std::uniform_real_distribution<> randomInfection(0, 1);
    int randomInfected = individuals(gen); // Generate a random index
    test.infect(population[randomInfected]); // Use your Virus.infect() method

    // Begin the simulation loop
    for (i = 0; i <= SIMULATION_DAYS; i++)
    {
        for (int k = 0; k < N; k++) {
            Individual& person = population[k]; // Use reference

            if (person.getHealthStatus() == HealthStatus::Infected)
            {
                test.severity(person);
                person.incrementInfectionDays();

                if (k - 1 >= 0)
                {
                    test.spreadTo(population[k - 1]);
                }
                if (k + 1 < N)
                {
                    test.spreadTo(population[k + 1]);
                }
            }
            else {
                double randomInfectChance = randomInfection(gen);
                if (randomInfectChance < 0.0000002)
                {
                    test.infect(person);
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
    std::cout << "Infected Total: " << simulationData[0] << " / " << N << std::endl;
    std::cout << "Recovered Total: " << simulationData[1] << " / " << N << std::endl;
    std::cout << "Deceased Total: " << simulationData[2] << " / " << N << std::endl;
    return 0;
}
