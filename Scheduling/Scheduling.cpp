// Scheduling.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
// Prozess Scheduling von Finn Wiskandt, Martyna Dorosewicz, Dennis Venturini

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <random>

#include <Windows.h>

#include "Prozess.h"
#include "FirstComeFirstServe.h"
#include "ShortestJobFirst.h"
#include "EarliestDeadlineFirst.h"
#include "LeastLaxityFirst.h"
#include "RoundRobin.h"


bool CompareArrivalTimes(Prozess p1, Prozess p2){
    if (p1.m_timeArrival == p2.m_timeArrival) return false;
    return (p1.m_timeArrival >= p2.m_timeArrival);
}

void PrintHeader() {
    system("cls");
    std::cout << "Prozess Scheduling\nvon Finn Wiskandt, Martyna Dorosewicz, Dennis Venturini\n\n";
}

void WaitForUserInput(char userInput = {}) {
    system("pause");
    PrintHeader();
}

std::vector<Prozess> FillSimpleProzess(bool withRandomOrder = false, bool isArray = true) {

    std::array<Prozess, 5> firstList;
    firstList[0] = Prozess(isArray, 0, 22, 0);
    firstList[1] = Prozess(isArray, 0, 2 , 0);
    firstList[2] = Prozess(isArray, 0, 3 , 0);
    firstList[3] = Prozess(isArray, 0, 5 , 0);
    firstList[4] = Prozess(isArray, 0, 8 , 0);

    if (withRandomOrder){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(firstList.begin(), firstList.end(), std::default_random_engine(seed));
    }

    std::vector<Prozess> tempVectorObject;
    for (size_t i = 0; i < firstList.size(); i++) {
        tempVectorObject.push_back(firstList[i]);
    }

    return tempVectorObject;
}

void RoundRobinCalculate(float randomAverageWaitingTime = 0) {

    std::vector<Prozess> roundRobin = FillSimpleProzess();

    //RoundRobin
    int quantum = 3;
    RoundRobin rr(roundRobin, quantum);
    rr.Schedule();
    std::cout << "Round Robin (Q=" << quantum << "):  Durchschnittliche Wartezeit: " << rr.GetReadyTime() << "\n\n";

    std::cout << "Die durschnittliche Wartezeit der durchschnittlichen Wartezeiten bei zufaelliger Reihenfolge betraegt: " << randomAverageWaitingTime << "\nUnsere Reihenfolge aus der Vorlesung hat eine durchschnittliche Wartezeit von: " << rr.GetReadyTime();
    std::cout << "\nEs ergibt sich ein Muster, wenn die Prozesse mit der groesten Bedienzeit als letztes drankommen\nist die durchschnittliche Wartezeit geringer, da Prozesse deren Bedienzeit kleiner";
    std::cout << "\nsind, andere Prozesse durchschnittlich weniger lang warten lassen. Wenn die Bedienzeit kleiner als das Quantum ist\nmerkt man einen bedeutenden unterschied der Durchschnittlichen Wartezeit.";
    float diffRandomtoPreset = 0;
    if (rr.GetReadyTime() >= randomAverageWaitingTime){
        diffRandomtoPreset = rr.GetReadyTime() - randomAverageWaitingTime;
    }else{
        diffRandomtoPreset = randomAverageWaitingTime - rr.GetReadyTime();
    }

    std::cout << "\n\nDadurch laesst sich eine durchschnittliche Differenz von " << diffRandomtoPreset << " errechnen.\n";

}

void RoundRobinRandomCalculate() {

    std::vector<Prozess> roundRobin;
    int quantum = 3;
    float randomAverageWaitingTime = 0.0f;
    int numberOfLoopPasses = 12;

    for (size_t i = 0; i < numberOfLoopPasses; i++){
        roundRobin = FillSimpleProzess(true);
        //RoundRobin
        RoundRobin rr(roundRobin, quantum);
        rr.Schedule();
        std::cout << "RoundRobin zufaellige Prozesses Reihenfolge (In folgender Reihenfolge Eingetroffen):\n";
        for (size_t i = 0; i < roundRobin.size(); i++) {
            std::cout << "Prozess " << i + 1 << " Bedienzeit: " << roundRobin[i].m_timeToCalculate << "\n";
        }
        std::cout << "Round Robin (Q=" << quantum << "):  Durchschnittliche Wartezeit: " << rr.GetReadyTime() << "\n\n";
        randomAverageWaitingTime += rr.GetReadyTime();
    }

    randomAverageWaitingTime /= numberOfLoopPasses;

    roundRobin = FillSimpleProzess();
    std::cout << "RoundRobin Prozesse (In folgender Reihenfolge Eingetroffen):\n";
    for (size_t i = 0; i < roundRobin.size(); i++) {
        std::cout << "Prozess " << i + 1 << " Bedienzeit: " << roundRobin[i].m_timeToCalculate << "\n";
    }

    RoundRobinCalculate(randomAverageWaitingTime);


    WaitForUserInput();
}


void FirstComeFirstServedAndShortestJobFirstCalculate() {

    std::vector<Prozess> simpleProzess = FillSimpleProzess();

    FirstComeFirstServe fcfs(simpleProzess);
    fcfs.Schedule();

    PrintHeader();
    std::cout << "FCFS und SJF Prozesse (In folgender Reihenfolge Eingetroffen):\n";
    for (size_t i = 0; i < simpleProzess.size(); i++){
        std::cout << "Prozess " << i + 1 << " Bedienzeit: " << simpleProzess[i].m_timeToCalculate << "\n";
    }
    std::cout << "\nFirst Come First Serve Durchschnittliche Wartezeit: " << fcfs.GetReadyTime() << "\n\n";

    simpleProzess = FillSimpleProzess();

    //ShortestJobFirst
    ShortestJobFirst sjf(simpleProzess, false);
    sjf.Schedule();
    std::cout << "Shortest Job First     Durchschnittliche Wartezeit: " << sjf.GetReadyTime() << "\n\n";

    WaitForUserInput();
}

std::vector<Prozess> FillLaxity(bool isArray = true) {

    std::array<Prozess, 3> laxityList;
    laxityList[0] = Prozess(isArray, 0, 8, 10);
    laxityList[1] = Prozess(isArray, 0, 5, 9);
    laxityList[2] = Prozess(isArray, 0, 4, 9);

    std::vector<Prozess> tempVectorObject;
    for (size_t i = 0; i < laxityList.size(); i++) {
        tempVectorObject.push_back(laxityList[i]);
    }

    return tempVectorObject;
}

void LeastLaxityFirstCalculate() {

    std::vector<Prozess> laxity = FillLaxity();

    //LeastLaxityFirst
    LeastLaxityFirst llf(laxity);
    llf.Schedule();
    std::cout << "LLF (In folgender Reihenfolge Eingetroffen):\n";
    for (size_t i = 0; i < laxity.size(); i++) {
        std::cout << "Prozess " << i + 1 << " Bedienzeit: " << laxity[i].m_timeToCalculate << " Deadline: "<<laxity[i].m_deadline <<"\n";
    }
    std::cout << "Least Laxity First  Durchschnittliche Wartezeit: " << llf.GetReadyTime() << "\n\n";

    WaitForUserInput();
}

std::vector<Prozess> Filldeadline(bool isArray = true) {

    std::array<Prozess, 4> deadlineList;
    deadlineList[0] = Prozess(isArray, 0, 4, 5);
    deadlineList[1] = Prozess(isArray, 0, 1, 7);
    deadlineList[2] = Prozess(isArray, 0, 2, 7);
    deadlineList[3] = Prozess(isArray, 0, 5, 13);

    std::vector<Prozess> tempVectorObject;
    for (size_t i = 0; i < deadlineList.size(); i++) {
        tempVectorObject.push_back(deadlineList[i]);
    }

    return tempVectorObject;
}

void EarliestDeadlineFirstCalculate() {

    std::vector<Prozess> deadline = Filldeadline();

    //EarliestDeadlineFirst
    EarliestDeadlineFirst edf(deadline);
    edf.Schedule();
    std::cout << "EDF Prozesses (In folgender Reihenfolge Eingetroffen):\n";
    for (size_t i = 0; i < deadline.size(); i++) {
        std::cout << "Prozess " << i + 1 << " Bedienzeit: " << deadline[i].m_timeToCalculate << " Deadline: "<<deadline[i].m_deadline << "\n";
    }
    std::cout << "Earliest Deadline First  Durchschnittliche Wartezeit: " << edf.GetReadyTime() << "\n\n";

    WaitForUserInput();
}

std::vector<Prozess> FillPreemptiveSJF(bool withRandomOrder = false, bool isArray = true) {

    std::array<Prozess, 5> preemptiveList;
    preemptiveList[0] = Prozess(0, 22);
    preemptiveList[1] = Prozess(0, 2);
    preemptiveList[2] = Prozess(4, 3);
    preemptiveList[3] = Prozess(4, 5);
    preemptiveList[4] = Prozess(4, 8);

    if (withRandomOrder) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(preemptiveList.begin(), preemptiveList.end(), std::default_random_engine(seed));

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 10);
        for (size_t i = 0; i < preemptiveList.size(); i++){
            preemptiveList[i].m_timeArrival = distr(gen);
        }
    }

    std::vector<Prozess> tempVectorObject;
    for (size_t i = 0; i < preemptiveList.size(); i++) {
        tempVectorObject.push_back(preemptiveList[i]);
    }

    return tempVectorObject;
}

void ShortestJobFirstPreemptiveCalculate() {

    PrintHeader();

    std::vector<Prozess> preemtiveSJF = FillPreemptiveSJF();
    float randomAverageWaitingTime = 0.0f;
    int numberOfLoopPasses = 12;

    for (size_t i = 0; i < numberOfLoopPasses; i++) {
        preemtiveSJF = FillPreemptiveSJF(true);
        //ShortestJobFirst Preemptive
        ShortestJobFirst sjfPreemptive(preemtiveSJF, true);
        sjfPreemptive.Schedule();
        std::cout << "Shortest Job First zufaellige Prozesses Reihenfolge (In folgender Reihenfolge Eingetroffen):\n";
        for (size_t i = 0; i < preemtiveSJF.size(); i++) {
            std::cout << "Prozess " << i + 1 << " Bedienzeit: " << preemtiveSJF[i].m_timeToCalculate << "\n";
        }
        std::cout << "Shortest Job First Preemptive  Durchschnittliche Wartezeit: " << sjfPreemptive.GetReadyTime() << "\n\n";
        randomAverageWaitingTime += sjfPreemptive.GetReadyTime();
    }
    
    for (size_t i = 0; i < numberOfLoopPasses; i++) {
        preemtiveSJF = FillPreemptiveSJF(true);
        //ShortestJobFirst Non-Preemptive
        ShortestJobFirst sjf(preemtiveSJF, false);
        sjf.Schedule();
        std::cout << "Shortest Job First zufaellige Prozesses Reihenfolge (In folgender Reihenfolge Eingetroffen):\n";
        for (size_t i = 0; i < preemtiveSJF.size(); i++) {
            std::cout << "Prozess " << i + 1 << " Bedienzeit: " << preemtiveSJF[i].m_timeToCalculate << "\n";
        }
        std::cout << "Shortest Job First Non-Preemptive  Durchschnittliche Wartezeit: " << sjf.GetReadyTime() << "\n\n";
        randomAverageWaitingTime += sjf.GetReadyTime();
    }

    WaitForUserInput();

}

void ExamplesOrCustomProzessesUserInput() {

    PrintHeader();

    char usePresetProzessesUserInput;
    std::cout << "Vorlesungsbeispiele fuer berechnung benutzten?(y/n): ";
    std::cin.get(usePresetProzessesUserInput);

    if (usePresetProzessesUserInput != 'y'){
        Sleep(1000);
        return;
    }

    Sleep(1000);

    //FCFS and SJF and RoundRobin
    //FirstComeFirstServedAndShortestJobFirstCalculate();

    ////Laxity
    //LeastLaxityFirstCalculate();

    ////Earliest Deadline First
    //EarliestDeadlineFirstCalculate();

    ////Round Robin with random 
    //RoundRobinRandomCalculate();

    //Shortest Job First with random ready times
    ShortestJobFirstPreemptiveCalculate();

}

int main(){

    std::cout << "Prozess Scheduling\nby Finn Wiskandt, Martyna Dorosewicz, Dennis Venturini\n\n";
    system("pause");

    ExamplesOrCustomProzessesUserInput();

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
   /* Prozess tempProzess1(1, 1, 15);
    prozesse.push_back(tempProzess1);
    Prozess tempProzess2(2, 4, 10);
    prozesse.push_back(tempProzess2);
    Prozess tempProzess3(4, 1, 10);
    prozesse.push_back(tempProzess3);
    Prozess tempProzess4(1, 2, 5);
    prozesse.push_back(tempProzess4);*/
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
        ShortestJobFirst sjf(prozesse, true);
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
