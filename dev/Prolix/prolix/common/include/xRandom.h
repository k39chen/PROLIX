//====================================================================================
// @Title:      RANDOM
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/xRandom.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Provides a number of random number generator tools.
//
//====================================================================================
#ifndef __PROLIX_COMMON_RANDOM_H__
#define __PROLIX_COMMON_RANDOM_H__

//====================================================================================
//                                                                             xRandom
//====================================================================================
// unbounded random integer
int Random();

// bounded random integer
int Random(int min, int max);

// returns true if successful chance
bool Chance(float chance);

// runs through a specified number of test cases
void SimulateChance(float chance, int numExperiments = 100);

// returns a value with chanced deviation
int Deviation(int baseValue, int modValue, float chance);

// runs through a specified number of test cases
void SimulateDeviation(int baseValue, int modValue, float chance, int numExperiments = 10);

#endif