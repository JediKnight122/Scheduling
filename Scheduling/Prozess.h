#pragma once
class Prozess
{

public:
	unsigned int m_timeArrival=0;

	unsigned int m_timeTookToCalculate=0;

	unsigned int m_progession=0;
	unsigned int m_timeToCalculate=0;

	Prozess(unsigned int pTimeArrivel, unsigned int pTimeCalculation);
};

