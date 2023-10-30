cmake_minimum_required(VERSION 3.26)
project(AED2324_PRJ1_G56)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(AED2324_PRJ1_G56
        src/Lesson.cpp
        src/Lesson.h
        src/UcClass.cpp
        src/UcClass.h
        src/Student.cpp
        src/Student.h
        src/Dataset.cpp
        src/Dataset.h
        src/Request.cpp
        src/Request.h
        src/main.cpp
        src/Menu.cpp
        src/Menu.h
        src/Consult.cpp
        src/Consult.h
)
