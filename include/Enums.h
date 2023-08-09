#pragma once
#ifndef ENUMS
#define ENUMS

// Possible health statuses for an individual
enum class HealthStatus
{
	Normal,
	Immunocompromised,
	ChronicDisease,
	UnderlyingCondition,
	Elderly,
	Child,
	Pregnacy,
	Infected,
	Deceased
};

// Possible Infection statuses for an individual
enum class InfectionStatus
{
	Susceptible,
	Asymptomatic,
	Symptomatic,
	Quarantined,
	MildSymptoms,
	SevereSymptoms,
	CriticalCondition,
	Hospitalized,
	ICU,
	Recovered,
	Deceased
};

#endif