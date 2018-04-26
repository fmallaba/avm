cmake_minimum_required(VERSION 3.9)
project(avm)

set(CMAKE_CXX_STANDARD 11)

add_executable(avm main.cpp IOperand.h Operand.cpp Operand.h OpFactory.cpp OpFactory.h Exception.cpp Exception.h Parse.cpp Parse.h AVM.cpp AVM.h)