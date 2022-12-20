cmake_minimum_required(VERSION 3.21.1)
project(SchedulingCalculator_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(Scheduling)

add_executable(SchedulingCalculator_main
        Scheduling/EarliestDeadlineFirst.cpp
        Scheduling/EarliestDeadlineFirst.h
        Scheduling/FirstComeFirstServe.cpp
        Scheduling/FirstComeFirstServe.h
        Scheduling/LeastLaxityFirst.cpp
        Scheduling/Prozess.cpp
        Scheduling/Prozess.h
        Scheduling/RoundRobin.cpp
        Scheduling/RoundRobin.h
        Scheduling/Scheduling.cpp
        Scheduling/SchedulingStrategy.cpp
        Scheduling/SchedulingStrategy.h
        Scheduling/ShortestJobFirst.cpp
        Scheduling/ShortestJobFirst.h)
