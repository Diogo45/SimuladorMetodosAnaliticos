#pragma once
#include <queue>

enum EventType { ARRIVAL, DEPARTURE };

struct Event {
	float time;
	int queue_id;
	EventType event;

	Event(float time, int queue_id, EventType event) 
	{
		this->time = time;
		this->queue_id = queue_id;
		this->event = event;

	}

};



class Simulation {



private:


	struct CompareEvent {
		bool operator()(Event lhs, Event rhs)
		{
			return lhs.time > rhs.time;
		}
	};
	


public:

	Simulation(Simulation const&) = delete;

	void operator=(Simulation const&) = delete;

	std::priority_queue<Event, std::vector<Event>, CompareEvent> events;


	static Simulation& getInstance()
	{
		static Simulation instance;
		

		return instance;
	}

	Queue* queue;
	double global_time;

	Simulation() { };

	void StartQueue(Event inicialEvent);

	void ScheduleEvent(Event e);

	void Step();

	void CalculateStatistics();
};