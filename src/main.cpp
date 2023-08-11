#include <iostream>
#include <cstdlib>
#include "Individual.h"
#include "Enums.h"
#include "Utils.h"
#include "Virus.h"

constexpr int N = 1000;
constexpr int days = 365;

int main()
{
	// Generate population
	std::vector<Individual> population;

	for (int i = 0; i < N; i++)
	{
		int age = std::rand() % 100;
		population.push_back(Individual(i + 1, age, HealthStatus::Normal, InfectionStatus::Susceptible, 0));
	}

	Virus test(0.23, 3, 10, 0.1, 0.27);
	return 0;
}