#include "pch.h"
#include <iostream>
#include <string>

Queue::Queue(char arrival_dist, char serve_dist, int queue_size, float2 arrival_interval, float2 serve_interval, int server_quantity) : arrival_interval(0, 0), serve_interval(0, 0), rnd(5)
{
	this->current_queue_size = 0;
	this->arrival_dist = arrival_dist;
	this->serve_dist = serve_dist;
	this->queue_max_size = queue_size;
	this->arrival_interval = arrival_interval;
	this->serve_interval = serve_interval;
	this->server_quantity = server_quantity;

	queue_size++;
	queue_states = std::vector<float>(queue_size);


}

void Queue::Arrival(double time)
{

	queue_states[current_queue_size] += time - Simulation::getInstance().global_time;
	Simulation::getInstance().global_time += time - Simulation::getInstance().global_time;

	if (current_queue_size < queue_max_size) {
		current_queue_size++;

		if (current_queue_size <= server_quantity) {
			Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + rnd.GetRandom(serve_interval.x, serve_interval.y), 0, EventType::DEPARTURE));
		}
	}

	Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + rnd.GetRandom(arrival_interval.x, arrival_interval.y), 0, EventType::ARRIVAL));

#ifdef DEBUG
	PrintStates();

#endif // DEBUG


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
	queue_states[current_queue_size] += time - Simulation::getInstance().global_time;
	Simulation::getInstance().global_time += time - Simulation::getInstance().global_time;
	current_queue_size--;
	if (current_queue_size >= server_quantity) {
		Simulation::getInstance().ScheduleEvent(Event(Simulation::getInstance().global_time + rnd.GetRandom(serve_interval.x, serve_interval.y), 0, EventType::DEPARTURE));
	}

#ifdef DEBUG
	PrintStates();

#endif // DEBUG
}