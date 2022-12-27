#include "ShortestJobFirst.h"

#include <algorithm>

bool ShortestJobFirst::CompareJobLenghts(Prozess p1, Prozess p2)
{
    if (p1.m_timeToCalculate == p2.m_timeToCalculate) return false;
    return (p1.m_timeToCalculate < p2.m_timeToCalculate);
}

ShortestJobFirst::ShortestJobFirst(std::vector<Prozess>& pProzesses, bool preemtiv): SchedulingStrategy(pProzesses)
{
    std::stable_sort(m_Prozesses.begin(), m_Prozesses.end(), &ShortestJobFirst::CompareJobLenghts);
	m_preemtiv = preemtiv;
}

void ShortestJobFirst::Schedule()
{
	if (m_preemtiv) SchedulePreemtiv();
	else ScheduleNonPreemtiv();
	
}

void ShortestJobFirst::SchedulePreemtiv()
{
	for (size_t i = 0; i < m_Prozesses.size(); i++)
	{
		if (m_Prozesses[i].m_timeArrival > m_timePassed)
		{
			//Preemtive: Falls erster Prozess nicht bereit, durchsuche alle weiteren
			//und rechne ggf. einen. Nach einer Zeiteinheit für den anderen Prozess,
			//prüfe wieder, ob andere Prozesse bereit sind
			for (size_t j = i; j < m_Prozesses.size(); j++)
			{
				//Falls Prozess bereit und nicht fertig
				if (m_Prozesses[j].m_timeArrival <= m_timePassed && m_Prozesses[i].m_progession < m_Prozesses[i].m_timeToCalculate)
				{

					m_Prozesses[j].m_progession++;
					m_timePassed++;

					m_Prozesses[j].m_timeTookToCalculate = m_timePassed;
					break;
				}
			}
			i--;
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

void ShortestJobFirst::ScheduleNonPreemtiv()
{
	for (size_t i = 0; i < m_Prozesses.size(); i++)
	{
		if (m_Prozesses[i].m_timeArrival > m_timePassed)
		{
			//Non-Preemtive: Falls erster Prozess nicht bereit, durchsuche alle weiteren
			//und rechne ggf. einen. Nachdem einer gerechnet wurde: Break 
			for (size_t j = i; j < m_Prozesses.size(); j++)
			{
				//Falls Prozess bereit und nicht fertig
				if (m_Prozesses[j].m_timeArrival <= m_timePassed && m_Prozesses[j].m_timeTookToCalculate == 0)
				{

					while (m_Prozesses[j].m_progession < m_Prozesses[j].m_timeToCalculate) {
						m_Prozesses[j].m_progession++;
						m_timePassed++;
					}
					m_Prozesses[j].m_timeTookToCalculate = m_timePassed;
					break;
				}
			}
			i--;
			continue;
		}
		while (m_Prozesses[i].m_progession < m_Prozesses[i].m_timeToCalculate) {
			m_Prozesses[i].m_progession++;
			m_timePassed++;
			m_Prozesses[i].m_timeTookToCalculate = m_timePassed;
		}

		
	}

	CalculateReadyTime();
}
