//====================================================================================
// @Title:      RANDOM
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/xRandom.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include "../include/xRandom.h"
#include "../include/xString.h"

//====================================================================================
//                                                                             xRandom
//====================================================================================
int Random()
{
	return rand();
}

int Random(int min, int max)
{
	return rand()%(max - min) + min;
}

bool Chance(float chance)
{
	if (chance <= 0.0f) return false;
	if (chance >= 1.0f) return true;

	std::string str = toString<float>(chance).substr(2);
	int set = (int)pow(10.0, (double)str.length());

	int iChance = (int)ToNumber(str);

	return (Random(0, set) <= iChance);
}

void SimulateChance(float chance, int numExperiments)
{
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << " Random Number Simulator                          " << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << " Expect " << chance * 100 << "% success\t\t" << numExperiments << " simulations" << std::endl;

	int successes = 0;
	int failures = 0;

	for (int i=0;i<numExperiments;i++)
	{
		Chance(chance)? successes++ : failures++ ;
	}
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << " SUCCESSES:\t" << successes << "/" << numExperiments << "\t\t" << std::setprecision(2) << (float)successes / (float)numExperiments << std::endl;
	std::cout << " FAILURES:\t" << failures << "/" << numExperiments << "\t\t" << std::setprecision(2) << (float)failures / (float)numExperiments << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
}

int Deviation(int baseValue, int modValue, float chance)
{
	int newValue = baseValue;

	if (Chance(0.50f))	// incrementing from base value
	{
		newValue = newValue + modValue * Random(0, (int)(100 * chance)) / 100;
	}
	else	// decrementing from base value
	{
		newValue = newValue - modValue * Random(0, (int)(100 * chance)) / 100;
	}
	
	return newValue;
}

void SimulateDeviation(int baseValue, int modValue, float chance, int numExperiments)
{
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << " Random Deviation Simulator                       " << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << " Base Value:\t" << baseValue << std::endl;
	std::cout << " Mod Value:\t" << modValue << std::endl;
	std::cout << " Chance:\t" << chance * 100 << "%" << std::endl;
	std::cout << " Experiments:\t" << numExperiments << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
	for (int i=0;i<numExperiments;i++)
	{
		std::cout << " " <<  i + 1 << ">\t";
		
		int num = Deviation(baseValue, modValue, chance);
		
		if (num < baseValue)
		{
			std::cout << num << "\t-" << baseValue - num;
		}
		else if (num > baseValue)
		{
			std::cout << num << "\t+" << num - baseValue;
		}
		else
		{
			std::cout << num << "\t/0";
		}

		std::cout << std::endl;
	}
	std::cout << "--------------------------------------------------" << std::endl;
}