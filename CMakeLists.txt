cmake_minimum_required(VERSION 3.6)
project(BankSystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Random.h ServiceWindow.h Node.h Event.h Queue.h QueueSystem.cpp QueueSystem.h)
add_executable(BankSystem ${SOURCE_FILES})