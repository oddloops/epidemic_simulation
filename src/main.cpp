#include <iostream>
#include "Individual.h"
#include "Enums.h"
#include "Utils.h"

int main()
{
	Individual test(1, 50, HealthStatus::Normal, InfectionStatus::Susceptible);

	// Test if declared correctly
	std::cout << "ID: " << test.getID() << std::endl;
	std::cout << "Age: " << test.getAge() << std::endl;
	std::cout << "Health Status: " << static_cast<int>(test.getHealthStatus()) << std::endl;
	std::cout << "Infection Status: " << static_cast<int>(test.getInfectionStatus()) << std::endl;

	// Test setters
	test.updateHealthStatus(HealthStatus::Infected);
	test.updateInfectionStatus(InfectionStatus::CriticalCondition);

	// Output object attributes
	std::cout << "New Health Status: " << static_cast<int>(test.getHealthStatus()) << std::endl;
	std::cout << "New Infection Status: " << static_cast<int>(test.getInfectionStatus()) << std::endl;
	return 0;
}