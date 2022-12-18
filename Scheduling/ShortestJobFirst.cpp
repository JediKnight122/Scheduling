#include "ShortestJobFirst.h"

#include <algorithm>

bool ShortestJobFirst::CompareJobLenghts(Prozess p1, Prozess p2)
{
    if (p1.m_timeToCalculate == p2.m_timeToCalculate) return false;
    return (p1.m_timeToCalculate >= p2.m_timeToCalculate);
}

ShortestJobFirst::ShortestJobFirst(std::vector<Prozess>& pProzesses): SchedulingStrategy(pProzesses)
{
    std::stable_sort(m_Prozesses.begin(), m_Prozesses.end(), &ShortestJobFirst::CompareJobLenghts);
}

void ShortestJobFirst::Schedule()
{
	for(size_t i=0; i<m_Prozesses.size(); i++)
	{
		while (m_Prozesses[i].m_progession < m_Prozesses[i].m_timeToCalculate) {
			m_Prozesses[i].m_progession++;
			m_timePassed++;
		}

		m_Prozesses[i].m_timeTookToCalculate = m_timePassed;
	}

	CalculateReadyTime();
}
