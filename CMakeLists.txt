cmake_minimum_required (VERSION 2.6) 
project (Neuron) 

set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -Wextra -std=c++11 -g -pg") 

enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable (Neuron neuron_main.cpp network.cpp neuron.cpp)
add_executable(neuron_unittest neuron.cpp network.cpp unittest.cpp) 

target_link_libraries(neuron_unittest gtest gtest_main) 
add_test(neuron_unittest unittest) 
