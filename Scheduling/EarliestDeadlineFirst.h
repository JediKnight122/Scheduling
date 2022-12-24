#pragma once
#include "SchedulingStrategy.h"
#include <algorithm>
#include <vector>

class EarliestDeadlineFirst: public SchedulingStrategy
{
private:
    std::vector<Prozess> prozesseOpen;
    std::vector<Prozess> prozesseDone;
    unsigned int timeNow = 0;
    int sizeAll = 0;

public:
    EarliestDeadlineFirst(std::vector<Prozess> &pProzesses);
    void Schedule() override;
    void Sort(std::vector<Prozess>& pProzesses);
    static bool CompareDeadlineLenghts(Prozess p1, Prozess p2);
};

