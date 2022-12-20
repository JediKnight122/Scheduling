//
// Created by Marty on 20.12.2022.
//

#ifndef SCHEDULINGCALCULATOR_MAIN_LEASTLAXITYFIRST_H
#define SCHEDULINGCALCULATOR_MAIN_LEASTLAXITYFIRST_H

#include <algorithm>
#include <vector>
#include "SchedulingStrategy.h"


class LeastLaxityFirst: public SchedulingStrategy {
private:
    std::vector<Prozess> prozesseOpen;
    std::vector<Prozess> prozesseDone;
    int timeNow=0;
    int sizeAll;

public:
    LeastLaxityFirst(std::vector<Prozess> &pProzesses);
    void Schedule() override;
    void Sort(std::vector<Prozess>& pProzesses);
    static bool CompareLaxity(Prozess p1, Prozess p2);
    void CalcLaxity(std::vector<Prozess>& pProzesses);
};


#endif //SCHEDULINGCALCULATOR_MAIN_LEASTLAXITYFIRST_H
