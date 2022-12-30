#pragma once
// Prozess Scheduling von Finn Wiskandt, Martyna Dorosewicz, Dennis Venturini
class Prozess
{

public:
	unsigned int m_timeArrival=0;
	unsigned int m_timeToCalculate=0;
	unsigned int m_timeRemainingToCalculate = 0;

	unsigned int m_timeTookToCalculate=0;
	
	unsigned int m_progession=0;

	unsigned int m_deadline=0;
	unsigned int m_doneTime=0;
	unsigned int m_laxity=0;
    bool dead=false;

	Prozess();
	Prozess(bool isArray, unsigned int m_timeArrival, unsigned int m_timeToCalculate, unsigned int m_deadLine);
	Prozess(unsigned int pTimeArrival, unsigned int pTimeCalculation);
	Prozess(unsigned int pTimeArrival, unsigned int pTimeCalculation, unsigned int pDeadLine);
	void UpdateRemainingTime();
};

