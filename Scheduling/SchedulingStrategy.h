#pragma once
#include "Prozess.h"
#include <vector>
// Prozess Scheduling von Finn Wiskandt, Martyna Dorosewicz, Dennis Venturini

class SchedulingStrategy
{
protected:
	float m_ReadyTime = 0;
	unsigned int m_timePassed = 0;

	virtual void CalculateReadyTime(); //Antwortzeit

public:
	SchedulingStrategy(std::vector<Prozess> &pProzesses);

	virtual float GetReadyTime();

	std::vector<Prozess> m_Prozesses;

	virtual void Schedule() = 0;
	
	
};

