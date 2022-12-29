#pragma once
#include "SchedulingStrategy.h"
// Prozess Scheduling von Finn Wiskandt, Martyna Dorosewicz, Dennis Venturini

class FirstComeFirstServe: public SchedulingStrategy
{
public:
	 FirstComeFirstServe(std::vector<Prozess> &pProzesses);
	 //float CalculateReadyTime();

	void Schedule() override;
};

