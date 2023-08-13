#include "Utils.h"

// Function declaration for generateAge
int generateAge(std::mt19937& gen, const std::map<std::pair<int, int>, double>& distribution)
{
	std::uniform_real_distribution<double> agePercentage(0.0, 1.0);
	double randomPercentage = agePercentage(gen);

	double cumalitiveProbability = 0.0;
	for (const auto& ages : distribution)
	{
		// Add the probability of the age group
		cumalitiveProbability += ages.second;
		if (randomPercentage <= cumalitiveProbability)
		{
			int ageLowerBound = ages.first.first;
			int ageUpperBound = ages.first.second;
			std::uniform_int_distribution<> age(ageLowerBound, ageUpperBound);
			return age(gen);
		}
	}
	return -1;
}

int getAgeRange(int age)
{
	if (age >= 0 && age < 15)
	{
		return 0;
	}
	else if (age < 65)
	{
		return 1;
	}
	else if (age <= 100)
	{
		return 2;
	}
	else {
		return -1;
	}
	return -1;
}

// Statuses to string functions
std::string healthToString(HealthStatus status)
{
	switch (status)
	{
		case HealthStatus::Normal:
			return "Normal";
		case HealthStatus::Infected:
			return "Infected";
		case HealthStatus::Immunocompromised:
			return "Immunocompromised";
		case HealthStatus::ChronicDisease:
			return "Chronic Disease";
		case HealthStatus::UnderlyingCondition:
			return "Underlying Condition";
		case HealthStatus::Elderly:
			return "Elderly";
		case HealthStatus::Child:
			return "Child";
		case HealthStatus::Pregnacy:
			return "Pregnacyl";
		case HealthStatus::Recovered:
			return "Recovered";
		case HealthStatus::Deceased:
			return "Deceased";
		default:
			return "Unknown";
	}
}

std::string infectionToString(InfectionStatus status)
{
	switch (status)
	{
		case InfectionStatus::Susceptible:
			return "Susceptible";
		case InfectionStatus::Asymptomatic:
			return "Asymptomatic";
		case InfectionStatus::Symptomatic:
			return "Symptomatic";
		case InfectionStatus::Quarantined:
			return "Quarantined";
		case InfectionStatus::MildSymptoms:
			return "MildSymptoms";
		case InfectionStatus::SevereSymptoms:
			return "SevereSymptoms";
		case InfectionStatus::CriticalCondition:
			return "CriticalCondition";/*
		case InfectionStatus::Hospitalized:
			return "Hospitalized";
		case InfectionStatus::ICU:*/
			return "ICU";
		case InfectionStatus::Recovered:
			return "Recovered";
		case InfectionStatus::Deceased:
			return "Deceased";
		default:
			return "Unknown";
	}
}