// SimuladorMetodosAnaliticos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>






int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Please specify topology file!" << std::endl;
		return -1;
	}

	//std::cout << "Started Parsing Topology" << std::endl;
	Simulation::getInstance().ParseTopology(argv[1]);
	//std::cout << "Finished Parsing Topology" << std::endl;
	/*Simulation::getInstance().StartSimulation();

	Queue* queue = new Queue(0, 3, float2(2, 3), float2(2, 5), 2);
	Queue* queue2 = new Queue(1, 3, float2(1, 2), float2(3, 5), 1);

	Simulation::getInstance().AddQueue(queue);
	Simulation::getInstance().AddQueue(queue2);

	Simulation::getInstance().AddConnection(0, Connection(1, 1.0));

	Simulation::getInstance().ScheduleEvent(Event(2.5, queue->queue_id, EventType::ARRIVAL));*/


	for (size_t i = 0; i < 100; i++)
	{
		Simulation::getInstance().Step();

	}

	Simulation::getInstance().CalculateStatistics();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
