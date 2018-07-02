#pragma once

#include "Graphic.hpp"
#include "Time.hpp"

class	Game
{
	Graphic _graphic;
	bool _running;

	// _moveCycle is set to true every _cycleTime seconds
	Time _clock;
	double _lastCycleTime;
	static constexpr double _cycleTime = 0.5;
	bool _moveCycle;

	// use these values instead of qeurying _graphic for them
	bool _left;
	bool _right;
	

	void	pollInput(void);
	void	initMap(void);
	void	move(void);
	void	render(void);
	
	
public:

	Game(glm::ivec2 mapsize);
	~Game(void);

	void	Run(void);
	bool	ShouldRun(void);
};
