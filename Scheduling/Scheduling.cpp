// Scheduling.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <algorithm>
#include <iostream>
#include <vector>


#include "FirstComeFirstServe.h"
#include "Prozess.h"
#include "RoundRobin.h"
#include "ShortestJobFirst.h"

bool CompareArrivalTimes(Prozess p1, Prozess p2)
{
    if (p1.m_timeArrival == p2.m_timeArrival) return false;
    return (p1.m_timeArrival >= p2.m_timeArrival);
}
int main()
{
    int anzProzesse = 0;
    std::vector<Prozess> prozesse;
    int tempAnkunft = 0;
    int tempDauer = 0;

    std::cout << "Wie viele Prozesse?" << std::endl;
    std::cin >> anzProzesse;

    for (int i = 0; i < anzProzesse; ++i) {
        std::cout << "Prozess: " << (i + 1) << " Ankunftzeit:" << std::endl;
        std::cin >> tempAnkunft;

        std::cout << "Prozess: " << (i + 1) << " Dauer:" << std::endl;
        std::cin >> tempDauer;

        Prozess tempProzess(tempAnkunft, tempDauer);

        prozesse.push_back(tempProzess);
    }


    std::stable_sort(prozesse.begin(), prozesse.end(), CompareArrivalTimes);


    RoundRobin rr(prozesse, 1);
    rr.Schedule();
    std::cout << "Round Robin (Q=1):  Durchschnittliche Wartezeit:" << rr.GetReadyTime() << std::endl;

    //Round Robin erhält unsortierten Vektor!
    RoundRobin rr2(prozesse, 2);
    rr2.Schedule();
    std::cout << "Round Robin (Q=2):  Durchschnittliche Wartezeit:" << rr2.GetReadyTime() << std::endl;


    //Round Robin erhält unsortierten Vektor!
    RoundRobin rr4(prozesse, 4);
    rr4.Schedule();
    std::cout << "Round Robin (Q=4):  Durchschnittliche Wartezeit:" << rr4.GetReadyTime() << std::endl;

    
    

    //Strategien anlegen
    
    FirstComeFirstServe fcfs(prozesse);
    fcfs.Schedule();
    std::cout<<"First Come First Serve:  Durchschnittliche Wartezeit:" << fcfs.GetReadyTime() <<std::endl;

    ShortestJobFirst sjf(prozesse);
    sjf.Schedule();
    std::cout << "Shortest Job First:  Durchschnittliche Wartezeit:" << sjf.GetReadyTime() << std::endl;


}
