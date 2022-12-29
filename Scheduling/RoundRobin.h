#pragma once
#include "SchedulingStrategy.h"

// Prozess Scheduling von Finn Wiskandt, Martyna Dorosewicz, Dennis Venturini
class RoundRobin : public SchedulingStrategy
{
public:
	void Schedule() override;
	
	RoundRobin(std::vector<Prozess>& pProzesses, int pZeitscheibe);

private:
	int m_Zeitscheibe = 1;
};

