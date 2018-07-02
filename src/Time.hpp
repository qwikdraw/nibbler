#pragma once

#include <chrono>

class	Time
{
private:
	
	std::chrono::high_resolution_clock::time_point _startTime;
	std::chrono::high_resolution_clock::time_point _delta;
	float _totalTime;
	float _deltaTime;

public:

	Time(void);
	
	void	Reset(void);
	void	Step(void);
	double	Total(void);
	double	Delta(void);
};
