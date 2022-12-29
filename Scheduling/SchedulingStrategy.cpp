#include "SchedulingStrategy.h"
// Prozess Scheduling von Finn Wiskandt, Martyna Dorosewicz, Dennis Venturini
void SchedulingStrategy::CalculateReadyTime()
{
	for (size_t i = 0; i< m_Prozesses.size(); i++)
	{
		m_ReadyTime += (m_Prozesses[i].m_timeTookToCalculate- m_Prozesses[i].m_timeArrival);
	}

	m_ReadyTime /= m_Prozesses.size();
}

SchedulingStrategy::SchedulingStrategy(std::vector<Prozess> &pProzesses)
{
	m_Prozesses = pProzesses;
}

float SchedulingStrategy::GetReadyTime()
{
	return m_ReadyTime;
}

