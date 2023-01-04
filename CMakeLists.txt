cmake_minimum_required(VERSION 3.25)
project(shared_whiteboard)


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(shared_whiteboard main.cpp)

target_link_libraries( shared_whiteboard ${OpenCV_LIBS} )
target_link_libraries(shared_whiteboard sfml-graphics sfml-audio)