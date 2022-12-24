//
// Created by Marty on 20.12.2022.
//

#include "LeastLaxityFirst.h"

LeastLaxityFirst::LeastLaxityFirst(std::vector<Prozess> &pProzesses) : SchedulingStrategy(pProzesses) {
    CalcLaxity(m_Prozesses);
}

void LeastLaxityFirst::Schedule() {
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

void LeastLaxityFirst::Sort(std::vector<Prozess> &pProzesses) {
    std::stable_sort(pProzesses.begin(), pProzesses.end(), &LeastLaxityFirst::CompareLaxity);
}

bool LeastLaxityFirst::CompareLaxity(Prozess p1, Prozess p2) {
    if (p1.m_laxity == p2.m_laxity) return false;
    return (p1.m_laxity < p2.m_laxity);
}

void LeastLaxityFirst::CalcLaxity(std::vector<Prozess> &pProzesses) {
    for (size_t i = 0; i < pProzesses.size(); ++i) {
        pProzesses[i].m_laxity=pProzesses[i].m_deadline-pProzesses[i].m_timeArrival-pProzesses[i].m_timeToCalculate;
    }
}
