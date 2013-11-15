//====================================================================================
// @Title:      VECTOR
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/xVector.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/xVector.h"

std::vector<int> arrayToVector (int arr[], int size) 
{
	std::vector<int> tmp(0);
	tmp.insert(tmp.begin(), arr, arr + size);
	return tmp;
}