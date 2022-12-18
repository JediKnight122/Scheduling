#pragma once
#include "SchedulingStrategy.h"

class FirstComeFirstServe: public SchedulingStrategy
{
public:
	 FirstComeFirstServe(std::vector<Prozess> &pProzesses);
	 //float CalculateReadyTime();

	void Schedule() override;
};

