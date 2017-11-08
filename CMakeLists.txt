cmake_minimum_required (VERSION 2.6) 
project (Neuron) 

set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -Wextra -std=c++11 -g -pg") 

enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable (Neuron neuron_main.cpp network.cpp neuron.cpp experiment.cpp)
add_executable(neuron_unittest neuron.cpp network.cpp unittest.cpp) 

target_link_libraries(neuron_unittest gtest gtest_main)
add_test(neuron_unittest unittest) 

find_package(Doxygen) 
IF(DOXYGEN_FOUND) 
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Usermanual.in)
message(FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
         - ${CMAKE_CURRENT_SOURCE_DIR}/Usermanual.in not found.
         - Generate one in the project folder with doxygen -g Usermanual.in")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Usermanual.in)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Usermanual.in ${CMAKE_CURRENT_BINARY_DIR}/Usermanual @ONLY)
add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Usermanual 
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
ELSE(DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF(DOXYGEN_FOUND)
