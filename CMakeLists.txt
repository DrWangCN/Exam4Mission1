cmake_minimum_required(VERSION 3.12)

project(mission1)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(mission1 main.cpp ProcessCSV.cpp ProcessCSV.h)

target_link_libraries(mission1 ${OpenCV_LIBS})

