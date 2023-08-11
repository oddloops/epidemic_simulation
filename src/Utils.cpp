#include "Utils.h"

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