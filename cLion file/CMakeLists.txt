cmake_minimum_required(VERSION 3.23)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp Server.cpp Server.h Sensor.h Scheduler.cpp Scheduler.h)
