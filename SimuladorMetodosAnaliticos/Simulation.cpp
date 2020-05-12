#include "pch.h"
#include <iostream>
#include <fstream>

//#define DEBUG

void Simulation::ParseTopology(std::string file)
{
	std::ifstream topology;
	//std::cout << file << std::endl;
	std::string line;
	int state = -1;

	topology.open(file);

	StartSimulation();
	//std::cout << "Start" << std::endl;


	while (std::getline(topology, line).good())
	{

		//std::cout << "Line: " << line << std::endl;


		if (line.find("//") != std::string::npos)
		{
			//std::cout << "Pass Comment" << std::endl;

			continue;
		}
		if (line.find("Queues:") != std::string::npos)
		{
			//std::cout << "State queues" << std::endl;

			state = 0;
			continue;
		}
		if (line.find("Connections:") != std::string::npos)
		{
			//std::cout << "State Connections" << std::endl;

			state = 1;
			continue;
		}
		if (line.find("InitialArrival:") != std::string::npos)
		{
			//std::cout << "State Arrivals" << std::endl;

			state = 2;
			continue;
		}

		if (line.find("Constants:") != std::string::npos)
		{
			//std::cout << "State Arrivals" << std::endl;

			state = 3;
			continue;
		}

		if (state == 0)
		{
			std::vector<std::string> split;
			Split(line, ";", split);

			//std::cout << "Split Queue" << std::endl;
			bool infinity = false;

			int id = std::atoi(split.at(0).c_str());
			int server_qtd = std::atoi(split.at(1).c_str());

			//std::cout << "Added Queue" << server_qtd << std::endl;


			int capacity = std::atoi(split.at(2).c_str());
			if (capacity == -1) {
				
				capacity = -1;
				infinity = true;

			}
			float minArrival = std::atof(split.at(3).c_str());
			float maxArrival = std::atof(split.at(4).c_str());
			float minServe = std::atof(split.at(5).c_str());
			float maxServe = std::atof(split.at(6).c_str());

			//std::cout << "Convert Queue" << std::endl;


			Queue* newQueue = new Queue(id, capacity, float2(minArrival, maxArrival), float2(minServe, maxServe), server_qtd);

			newQueue->infinity = infinity;

			Simulation::getInstance().AddQueue(newQueue);


			//delete(&split);
		}

		if (state == 1)
		{
			std::vector<std::string> split;
			Split(line, ";", split);
			//std::cout << "Split Connection" << std::endl;

			int id = std::atoi(split.at(0).c_str());
			int id2 = std::atoi(split.at(1).c_str());
			float chance = std::atof(split.at(2).c_str());

			Simulation::getInstance().AddConnection(id, Connection(id2, chance));
			//std::cout << "Added Connection" << std::endl;

			//delete(&split);
		}

		if (state == 2)
		{
			std::vector<std::string> split;
			Split(line, ";", split);
			//std::cout << "Split Event" << std::endl;

			int id = std::atoi(split.at(0).c_str());
			float time = std::atof(split.at(1).c_str());


			Simulation::getInstance().ScheduleEvent(Event(time, id, EventType::ARRIVAL));

			//std::cout << "Added Event" << std::endl;

			//delete(&split);
		}

		if(state == 3)
		{
			std::vector<std::string> split;
			Split(line, ";", split);
			//std::cout << "Split Event" << std::endl;

			int iter = std::atoi(split.at(1).c_str());
			float seed = std::atof(split.at(0).c_str());

			Simulation::getInstance().iter = iter;
			Simulation::getInstance().seed = seed;

		}

	}

	for (size_t i = 0; i < Simulation::getInstance().queueList.size(); i++)
	{
		std::sort(Simulation::getInstance().queueList.at(i)->queue_connections.begin(), Simulation::getInstance().queueList.at(i)->queue_connections.end(), ConnectionComparer());

	}

	Simulation::getInstance().rnd = new RandomNumberGenerator(Simulation::getInstance().seed);
	 
	topology.close();
}

void Simulation::StartSimulation()
{
	global_time = 0;
	queueList = std::vector<Queue*>();
}

void Simulation::AddQueue(Queue* queue)
{
	queueList.push_back(queue);
}

void Simulation::AddConnection(int queue_id, Connection connection)
{
	auto queue = queueList.at(queue_id);
	queue->queue_connections.push_back(connection);
}


void Simulation::CalculateStatistics()
{
	std::cout << "SEED: " << Simulation::getInstance().seed << " ITERACOES: " << Simulation::getInstance().iter << std::endl;

	for (size_t j = 0; j < queueList.size(); j++)
	{
		std::cout << "ESTADO DA FILA " << j << "	TEMPO		PROBABILIDADE" << std::endl;
		auto queue = queueList.at(j);

		for (size_t i = 0; i < queue->queue_states.size(); i++)
		{
			std::cout << i << "			" << queue->queue_states[i] << "		" << (queue->queue_states[i] / global_time) * 100.0 << std::endl;

			if (queue->queue_states[i] == 0.0) break;

		}

		std::cout << "PERDAS: " << queue->losses <<  std::endl << std::endl;
	}

	std::cout << "Tempo Total de Simulacao: "  << Simulation::getInstance().global_time << std::endl;

}

void Simulation::ScheduleEvent(Event e) {

	events.push(e);

#ifdef DEBUG
	std::priority_queue<Event, std::vector<Event>, CompareEvent> eventsCopy(events);


	std::cout << "EVENTS: ";

	for (size_t i = 0; i < events.size(); i++)
	{
		std::cout << eventsCopy.top().time << " ";
		eventsCopy.pop();
	}
	std::cout << std::endl;
#endif // DEBUG


}

void Simulation::Step() {

	Event event = events.top();
	events.pop();


	for (size_t i = 0; i < queueList.size(); i++)
	{
		auto queueTemp = queueList.at(i);
		queueTemp->queue_states[queueTemp->current_queue_size] += event.time - Simulation::getInstance().global_time;
	}

	Simulation::getInstance().global_time += event.time - Simulation::getInstance().global_time;

	auto queue = queueList.at(event.queue_id);

	if (event.event == EventType::ARRIVAL)
	{
#ifdef DEBUG
		std::cout << "ARRIVAL IN: " << event.time << std::endl;
#endif // DEBUG
		queue->Arrival(event.time);

	}
	else if (event.event == EventType::DEPARTURE)
	{
#ifdef DEBUG
		std::cout << "DEPARTURE IN: " << event.time << std::endl;
#endif // DEBUG
		queue->Serve(event.time);

	}
	else
	{
		//DECIDE NEXT QUEUE
		double decide = Simulation::getInstance().rnd->GetRandom();
		double totalChance = 0.0;


		for (size_t i = 0; i < queue->queue_connections.size(); i++)
		{
			auto connection = queue->queue_connections.at(i);
			totalChance += connection.chance;
			

			if (decide < totalChance)
			{




				queue->Transfer(event.time, queueList.at(connection.queue_id));
				return;
			}
			

		}


		queue->Serve(event.time);


	}





}

void Split(const std::string& str, const std::string& delim, std::vector<std::string>& parts) {
	size_t start, end = 0;
	while (end < str.size()) {
		start = end;
		while (start < str.size() && (delim.find(str[start]) != std::string::npos)) {
			start++;  // skip initial whitespace
		}
		end = start;
		while (end < str.size() && (delim.find(str[end]) == std::string::npos)) {
			end++; // skip to end of word
		}
		if (end - start != 0) {  // just ignore zero-length strings.
			parts.push_back(std::string(str, start, end - start));
		}
	}
}