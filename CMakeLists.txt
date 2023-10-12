cmake_minimum_required(VERSION 3.26)
project(AED2324_PRJ1_G56)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(AED2324_PRJ1_G56 main.cpp
        student.cpp
        student.h
        uc.cpp
        uc.h
        course.cpp
        course.h
        classUc.cpp
        classUc.h
        stdafx.h
)
