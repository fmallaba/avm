cmake_minimum_required(VERSION 3.9)
project(avm)

set(CMAKE_CXX_STANDARD 11)

add_executable(avm src/main.cpp includes/IOperand.h includes/Operand.h src/OpFactory.cpp includes/OpFactory.h src/Exception.cpp includes/Exception.h src/Parse.cpp includes/Parse.h src/AVM.cpp includes/AVM.h)