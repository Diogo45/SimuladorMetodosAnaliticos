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

class Queue 
{

private:

	char arrival_dist;
	char serve_dist;
	int queue_max_size;
	int server_quantity;

	float2 arrival_interval;
	float2 serve_interval;


	int current_queue_size;



public:

	std::vector<float> queue_states;

	RandomNumberGenerator rnd;

	void PrintStates();

	Queue(char arrival_dist, char serve_dist, int queue_size, float2 arrival_interval, float2 serve_interval, int server_quantity);

	void Arrival(double time);
	void Serve(double time);

};