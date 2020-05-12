#pragma once
#include <queue>
#include <vector>
#include <string>

enum EventType { ARRIVAL, DEPARTURE, TRANSFER };

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


void Split(const std::string& str, const std::string& delim, std::vector<std::string>& parts);


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

	std::vector<Queue*> queueList;
	double global_time;


	RandomNumberGenerator* rnd;

	Simulation() { };

	void ParseTopology(std::string file);

	void StartSimulation();

	void AddQueue(Queue* queue);

	void AddConnection(int queue_id, Connection connection);

	void ScheduleEvent(Event e);

	void Step();

	void CalculateStatistics();
};