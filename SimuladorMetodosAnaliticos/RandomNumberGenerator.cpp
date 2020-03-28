

#include "pch.h"
#include <cmath>

RandomNumberGenerator::RandomNumberGenerator(unsigned long seed)
{
	this->seed = seed;
	maxValueM = (long) pow(2, 32);
	multiplierA = 1664525;
	incrementC = 1013904223;
}

double RandomNumberGenerator::GetRandom()
{
	seed = (multiplierA * seed + incrementC) % maxValueM;
	return (double) seed / maxValueM;
}