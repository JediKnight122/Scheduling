#pragma once
#include "SchedulingStrategy.h"
class RoundRobin : public SchedulingStrategy
{
public:
	void Schedule() override;
	
	RoundRobin(std::vector<Prozess>& pProzesses, int pZeitscheibe);

private:
	int m_Zeitscheibe = 1;
};

