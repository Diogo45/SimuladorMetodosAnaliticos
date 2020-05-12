#include "pch.h"
#include <iostream>
#include <string>
#include <chrono>

Queue::Queue(int queue_id, int queue_size, float2 arrival_interval, float2 serve_interval, int server_quantity) : arrival_interval(0, 0), serve_interval(0, 0)
{
	this->queue_id = queue_id;
	this->current_queue_size = 0;
	this->losses = 0;

	if (queue_size == -1) 
	{
		this->queue_max_size = std::numeric_limits<int>::max();
		queue_states = std::vector<float>(1);

	}
	else 
	{
		this->queue_max_size = queue_size;
		queue_states = std::vector<float>(queue_size + 1);

	}
	this->arrival_interval = arrival_interval;
	this->serve_interval = serve_interval;
	this->server_quantity = server_quantity;
	//this->Simulation::getInstance().rnd->seed = 1;



	//std::cout << queue_states.max_size();
	//if (queue_max_size >= queue_states.max_size()) 
	//{
	//}
	//else {

	//	queue_states = std::vector<float>(queue_max_size);

	//}


}

void Queue::Arrival(double time)
{

	//if (current_queue_size >= queue_max_size)
	//{
	//	std::cout << "AAAAAA" << std::endl;
	//}

	if (current_queue_size < queue_max_size)
	{
		

		current_queue_size++;

		if (infinity && current_queue_size >= queue_states.size()) { queue_states.push_back(0); }


		if (current_queue_size <= server_quantity)
		{

			if (queue_connections.size() > 0)
			{


				Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + Simulation::getInstance().rnd->GetRandom(serve_interval.x, serve_interval.y), queue_id, EventType::TRANSFER));

			}
			else
			{
				Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + Simulation::getInstance().rnd->GetRandom(serve_interval.x, serve_interval.y), queue_id, EventType::DEPARTURE));
			}



		}
	}
	else {
		losses++;
	}

	Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + Simulation::getInstance().rnd->GetRandom(arrival_interval.x, arrival_interval.y), queue_id, EventType::ARRIVAL));

#ifdef DEBUG

	PrintStates();

#endif // DEBUG


}


void Queue::Transfer(double time, Queue* next)
{


	current_queue_size--;
	if (current_queue_size >= server_quantity) {


		if (queue_connections.size() > 0)
		{


			Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + Simulation::getInstance().rnd->GetRandom(serve_interval.x, serve_interval.y), queue_id, EventType::TRANSFER));

		}
		else
		{
			Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + Simulation::getInstance().rnd->GetRandom(serve_interval.x, serve_interval.y), queue_id, EventType::DEPARTURE));
		}
	}

	if (next->current_queue_size < next->queue_max_size)
	{
		next->current_queue_size++;

		if (next->infinity && next->current_queue_size >= next->queue_states.size()) { next->queue_states.push_back(0); }


		if (next->current_queue_size <= next->server_quantity)
		{
			if (next->queue_connections.size() > 0)
			{


				Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + Simulation::getInstance().rnd->GetRandom(next->serve_interval.x, next->serve_interval.y), next->queue_id, EventType::TRANSFER));

			}
			else
			{
				Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + Simulation::getInstance().rnd->GetRandom(next->serve_interval.x, next->serve_interval.y), next->queue_id, EventType::DEPARTURE));
			}
		}
	}
	else {

		next->losses++;
	}
	

}

void Queue::PrintStates()
{
	std::string s = "";
	for (size_t i = 0; i <= queue_max_size; i++)
	{
		s += std::to_string(queue_states[i]);
		s += " ";
	}

	std::cout << s << " " << Simulation::getInstance().global_time << std::endl;
}


void Queue::Serve(double time)
{

	current_queue_size--;
	if (current_queue_size >= server_quantity) {

		if (queue_connections.size() > 0)
		{


			Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + Simulation::getInstance().rnd->GetRandom(serve_interval.x, serve_interval.y), queue_id, EventType::TRANSFER));

		}
		else
		{
			Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + Simulation::getInstance().rnd->GetRandom(serve_interval.x, serve_interval.y), queue_id, EventType::DEPARTURE));
		}
	}
#ifdef DEBUG
	PrintStates();

#endif // DEBUG
}

