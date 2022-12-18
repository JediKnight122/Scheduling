#pragma once
#include "SchedulingStrategy.h"

class ShortestJobFirst: public SchedulingStrategy
{
public:
    void Schedule() override;
    ShortestJobFirst(std::vector<Prozess>& pProzesses);

private:
    static bool CompareJobLenghts(Prozess p1, Prozess p2);
    
};

