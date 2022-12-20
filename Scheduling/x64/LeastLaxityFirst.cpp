#include "LeastLaxityFirst.h"
#include <algorithm>

LeastLaxityFirst::LeastLaxityFirst(std::vector<Prozess> &pProzesses) : SchedulingStrategy(pProzesses) {
    std::stable_sort(m_Prozesses.begin(), m_Prozesses.end(), &LeastLaxityFirst::CompareLaxityLenghts);
}

void LeastLaxityFirst::Schedule() {

}

bool LeastLaxityFirst::CompareLaxityLenghts(Prozess p1, Prozess p2) {
    return false;
}
