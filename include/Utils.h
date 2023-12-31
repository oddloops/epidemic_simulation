#pragma once
#ifndef UTIL
#define UTIL

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "Enums.h"

// Process user input functions
template <typename T>
T getInputData(const std::string& prompt, T minValue, T maxValue)
{
	T inputValue;
	while (true)
	{
		std::cout << prompt;
		if (std::cin >> inputValue)
		{
			if (inputValue >= minValue && inputValue <= maxValue)
			{
				break;
			}
			else
			{
				std::cout << "Invalid Input. Please enter an input from " << minValue << " to " << maxValue << "." << std::endl;
			}
		}
		else {
			std::cout << "Invalid input. Please enter a valid number." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	return inputValue;
}

std::string healthToString(HealthStatus status);
std::string infectionToString(InfectionStatus status);

#endif