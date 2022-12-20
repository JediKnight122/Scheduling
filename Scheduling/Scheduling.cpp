// Scheduling.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <algorithm>
#include <iostream>
#include <vector>

#include "Prozess.h"
#include "FirstComeFirstServe.h"
#include "ShortestJobFirst.h"
#include "EarliestDeadlineFirst.h"
#include "LeastLaxityFirst.h"
#include "RoundRobin.h"


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
    int tempDeadline = 0;
    int strategie = 3; ////////////////////////////
    int quantum = 0;


    std::cout << "Welche Strategie?" << std::endl;
    std::cout << "(1) FirstComeFirstServe" << std::endl;
    std::cout << "(2) ShortestJobFirst" << std::endl;
    std::cout << "(3) EarliestDeadlineFirst" << std::endl;
    std::cout << "(4) LeastLaxityFirst" << std::endl;
    std::cout << "(5) RoundRobin" << std::endl;

    std::cin >> strategie;
    
    if (strategie == 5)
    {
        std::cout << "Quantum?" << std::endl;
        std::cin >> quantum;
        std::cout << std::endl;
    }
    
    std::cout << "Wie viele Prozesse?" << std::endl;
    std::cin >> anzProzesse;
    
    for (int i = 0; i < anzProzesse; ++i)
    {
        std::cout << "Prozess " << (i + 1) << ": Ankunftzeit" << std::endl << "->";
        std::cin >> tempAnkunft;

        std::cout << "Prozess " << (i + 1) << ": Dauer:" << std::endl << "->";
        std::cin >> tempDauer;

        if (strategie == 3 || strategie == 4)
        {
            std::cout << "Prozess " << (i + 1) << ": Deadline" << std::endl << "->";
            std::cin >> tempDeadline;
        }

        std::cout << "---------------------------------------------------" << std::endl;

        if (strategie == 3 || strategie == 4)
        {
            Prozess tempProzess(tempAnkunft, tempDauer, tempDeadline);
            prozesse.push_back(tempProzess);
        }
        else
        {
            Prozess tempProzess(tempAnkunft, tempDauer);
            prozesse.push_back(tempProzess);
        }
    }

    
    ///////////////////////////////////////////////test
    Prozess tempProzess1(1, 1, 15);
    prozesse.push_back(tempProzess1);
    Prozess tempProzess2(2, 4, 10);
    prozesse.push_back(tempProzess2);
    Prozess tempProzess3(4, 1, 10);
    prozesse.push_back(tempProzess3);
    Prozess tempProzess4(1, 2, 5);
    prozesse.push_back(tempProzess4);
    //////////////////////////////////////////////

    std::stable_sort(prozesse.begin(), prozesse.end(), CompareArrivalTimes);


    //Strategien anlegen
    if (strategie == 1)
    {
        //FirstComeFirstServe
        FirstComeFirstServe fcfs(prozesse);
        fcfs.Schedule();
        std::cout << "First Come First Serve:  Durchschnittliche Wartezeit:" << fcfs.GetReadyTime() << std::endl;
    }
    if (strategie == 2)
    {
        //ShortestJobFirst
        ShortestJobFirst sjf(prozesse);
        sjf.Schedule();
        std::cout << "Shortest Job First:  Durchschnittliche Wartezeit:" << sjf.GetReadyTime() << std::endl;
    }
    if (strategie == 3)
    {
        //EarliestDeadlineFirst
        EarliestDeadlineFirst edf(prozesse);
        edf.Schedule();
        std::cout << "Earliest Deadline First:  Durchschnittliche Wartezeit:" << edf.GetReadyTime() << std::endl;
    }
    if (strategie == 4)
    {
        //LeastLaxityFirst
        LeastLaxityFirst llf(prozesse);
        llf.Schedule();
        std::cout << "Least Laxity First:  Durchschnittliche Wartezeit:" << llf.GetReadyTime() << std::endl;
    }
    if (strategie == 5)
    {
        //RoundRobin
        RoundRobin rr(prozesse, quantum);
        rr.Schedule();
        std::cout << "Round Robin (Q=" << quantum << "):  Durchschnittliche Wartezeit:" << rr.GetReadyTime() <<
            std::endl;
    }

    /*
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
    
    */
}
