#pragma once
#include "SchedulingStrategy.h"
// Prozess Scheduling von Finn Wiskandt, Martyna Dorosewicz, Dennis Venturini

class ShortestJobFirst: public SchedulingStrategy
{
public:
    void Schedule() override;
    void SchedulePreemtiv();
    void ScheduleNonPreemtiv();
    ShortestJobFirst(std::vector<Prozess>& pProzesses, bool preemtiv);

private:
    static bool CompareJobLenghts(Prozess p1, Prozess p2);
    bool m_preemtiv = false;
    
};

