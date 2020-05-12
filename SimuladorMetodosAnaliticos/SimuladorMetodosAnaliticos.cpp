#include "pch.h"
#include <iostream>



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Please specify topology file!" << std::endl;
		return -1;
	}

	Simulation::getInstance().ParseTopology(argv[1]);



	for (size_t i = 0; i < 500000; i++)
	{
		Simulation::getInstance().Step();

	}

	Simulation::getInstance().CalculateStatistics();
}


