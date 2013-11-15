//====================================================================================
// @Title:      VECTOR
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/xVector.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Vector tools for general vector applications.
//
//====================================================================================
#ifndef __PROLIX_BASE_COMMON_VECTOR_H__
#define __PROLIX_BASE_COMMON_VECTOR_H__

#include <vector>

//====================================================================================
//                                                                             xVector
//====================================================================================
// gets the size of an array
template<typename T, int size>
int GetArrLength(T(&)[size])
{
    return size;
}

// prints out a vector separated by new lines
template <typename T> void printVector (std::vector<T> v) 
{
	for (std::vector<T>::iterator i=v.begin(); i!=v.end(); i++)
    {
		std::cout << *i << std::endl;
    }
}

// returns an integer vector given an integer array and size
std::vector<int> arrayToVector(int arr[], int size);

#endif