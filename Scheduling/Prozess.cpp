#include "Prozess.h"

Prozess::Prozess(unsigned pTimeArrivel, unsigned pTimeCalculation) : m_timeArrival(pTimeArrivel),
                                                                     m_progession(0), m_timeToCalculate(pTimeCalculation)
{
}
Prozess::Prozess(unsigned pTimeArrivel, unsigned pTimeCalculation, unsigned int pDeadline) : m_timeArrival(pTimeArrivel),
                                                                     m_progession(0),
                                                                     m_timeToCalculate(pTimeCalculation),
                                                                     m_deadline(pDeadline)
{
}
