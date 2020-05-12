#pragma once
#include <vector>


struct float2 {

public:
	float x;
	float y;

	float2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}


	float2(int x, int y)
	{
		this->x = (float)x;
		this->y = (float)y;
	}
};


struct Connection {

public:
	int queue_id;
	float chance;


	Connection(int queue_id, float chance) 
	{
		this->chance = chance;
		this->queue_id = queue_id;
	}


	


};


struct ConnectionComparer {


	bool operator()(Connection lhs, Connection rhs)
	{
		return lhs.chance > rhs.chance;
	}
};


class Queue 
{

private:

	char arrival_dist;
	char serve_dist;
	long long queue_max_size;
	int server_quantity;

	float2 arrival_interval;
	float2 serve_interval;





public:

	std::vector<float> queue_states;
	std::vector<Connection> queue_connections;
	int current_queue_size;

	bool infinity = false;

	int losses;

	void Transfer(double time, Queue* next);

	void PrintStates();

	Queue(int queue_id, int queue_size, float2 arrival_interval, float2 serve_interval, int server_quantity);
	int queue_id;
	void Arrival(double time);
	void Serve(double time);

};