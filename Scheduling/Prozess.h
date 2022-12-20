#pragma once
class Prozess
{

public:
	unsigned int m_timeArrival=0;

	unsigned int m_timeTookToCalculate=0;

	unsigned int m_progession=0;
	unsigned int m_timeToCalculate=0;

	unsigned int m_deadline=0;
	unsigned int m_doneTime=0;
	unsigned int m_laxity=0;
    bool dead=false;

	Prozess(unsigned int pTimeArrivel, unsigned int pTimeCalculation);
	Prozess(unsigned int pTimeArrivel, unsigned int pTimeCalculation,unsigned int pDeadline);
};

