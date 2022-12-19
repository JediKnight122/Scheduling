#include "RoundRobin.h"

void RoundRobin::Schedule()
{
	bool allProcessesFinished = false;
	int numProcessesFinished = 0;

	while(!allProcessesFinished)
	{
		for (size_t i = 0; i < m_Prozesses.size(); i++)
		{
			if (numProcessesFinished == m_Prozesses.size())
			{
				allProcessesFinished = true;
				break;
			}

			if (m_Prozesses[i].m_timeToCalculate == m_Prozesses[i].m_progession) continue;

			for(int j=0; j<m_Zeitscheibe; j++)
			{
				m_Prozesses[i].m_progession++;
				m_timePassed++;

				if (m_Prozesses[i].m_timeToCalculate == m_Prozesses[i].m_progession) {
					m_Prozesses[i].m_timeTookToCalculate = m_timePassed;
					numProcessesFinished++;
					break;
				}
			}
			
		}
	}
	CalculateReadyTime();
	
}

RoundRobin::RoundRobin(std::vector<Prozess>& pProzesses, int pZeitscheibe): SchedulingStrategy(pProzesses),
                                                                            m_Zeitscheibe(pZeitscheibe)
{
}
