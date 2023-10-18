cmake_minimum_required(VERSION 3.26)
project(AED2324_PRJ1_G56)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(AED2324_PRJ1_G56 src/main.cpp
        src/student.cpp
        src/student.h
        src/uc.cpp
        src/uc.h
        src/lesson.cpp
        src/lesson.h
        src/class.cpp
        src/class.h
        src/stdafx.h
        src/menu.cpp
        src/menu.h
        src/csvReader.cpp
        src/csvReader.h
        src/dataset.cpp
        src/dataset.h
)
