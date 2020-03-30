#include "pch.h"
#include <iostream>

//#define DEBUG

void Simulation::StartQueue(Event inicialEvent)
{
	queue = new Queue('G', 'G', 3, float2(1, 2), float2(3, 6), 5);
	global_time = 0;





	if (inicialEvent.event == EventType::ARRIVAL) {
		queue->Arrival(inicialEvent.time);
	}
	else {
		queue->Serve(inicialEvent.time);
	}



}

void Simulation::CalculateStatistics()
{
	std::cout << "ESTADO DA FILA		TEMPO		PROBABILIDADE" << std::endl;
	for (size_t i = 0; i < queue->queue_states.size(); i++)
	{
		std::cout << i << "			" << queue->queue_states[i] << "		" << (queue->queue_states[i] / global_time)*100.0 << std::endl;
	}
}

void Simulation::ScheduleEvent(Event e) {

	events.push(e);

	std::priority_queue<Event, std::vector<Event>, CompareEvent> eventsCopy(events);

#ifdef DEBUG
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

	if (event.event == EventType::ARRIVAL)
	{
#ifdef DEBUG
		std::cout << "ARRIVAL IN: " << event.time << std::endl;
#endif // DEBUG
		queue->Arrival(event.time);

	}
	else
	{
#ifdef DEBUG
		std::cout << "DEPARTURE IN: " << event.time << std::endl;
#endif // DEBUG
		queue->Serve(event.time);

	}



}