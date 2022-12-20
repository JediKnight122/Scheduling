#include "FirstComeFirstServe.h"



void FirstComeFirstServe::Schedule()
{
	for (int i = 0; i < m_Prozesses.size(); i++)
	{
		if(m_Prozesses[i].m_timeArrival>m_timePassed)
		{
			m_timePassed++;
			continue;
		}

		while (m_Prozesses[i].m_progession < m_Prozesses[i].m_timeToCalculate) {
			m_Prozesses[i].m_progession++;
			m_timePassed++;
		}

		m_Prozesses[i].m_timeTookToCalculate = m_timePassed;

	}

	CalculateReadyTime();
}

FirstComeFirstServe::FirstComeFirstServe(std::vector<Prozess> &pProzesses): SchedulingStrategy(pProzesses)
{
	m_timePassed = 0;
}
