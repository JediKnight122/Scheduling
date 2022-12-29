#include "EarliestDeadlineFirst.h"
#include <algorithm>

// Prozess Scheduling von Finn Wiskandt, Martyna Dorosewicz, Dennis Venturini
void EarliestDeadlineFirst::Schedule() {
    sizeAll = m_Prozesses.size();

    while (prozesseDone.size() != sizeAll) {
        for (size_t i = 0; i < m_Prozesses.size(); ++i) {
            if (m_Prozesses[i].m_timeArrival <= timeNow && !m_Prozesses[i].dead) {
                m_Prozesses[i].dead=true;
                prozesseOpen.push_back(m_Prozesses[i]);
            }
        }
        if (!prozesseOpen.empty()) {
            Sort(prozesseOpen);

            timeNow += prozesseOpen.front().m_timeToCalculate;
            prozesseOpen.front().m_doneTime = timeNow;
            prozesseDone.push_back(prozesseOpen.front());

            prozesseOpen.erase(prozesseOpen.begin());
        }else{
            timeNow++;
        }
    }
    for (size_t i = 0; i < prozesseDone.size(); ++i) {
        prozesseDone[i].m_timeTookToCalculate = prozesseDone[i].m_doneTime - prozesseDone[i].m_timeArrival;
    }
    for (size_t i = 0; i < prozesseDone.size(); i++) {
        m_ReadyTime += prozesseDone[i].m_timeTookToCalculate;
    }
    m_ReadyTime/=sizeAll;
}

bool EarliestDeadlineFirst::CompareDeadlineLenghts(Prozess p1, Prozess p2) {
    if (p1.m_deadline == p2.m_deadline) return false;
    return (p1.m_deadline < p2.m_deadline);
}

void EarliestDeadlineFirst::Sort(std::vector<Prozess> &pProzesses) {
    std::stable_sort(pProzesses.begin(), pProzesses.end(), &EarliestDeadlineFirst::CompareDeadlineLenghts);
}

EarliestDeadlineFirst::EarliestDeadlineFirst(std::vector<Prozess> &pProzesses) : SchedulingStrategy(pProzesses) {

}


