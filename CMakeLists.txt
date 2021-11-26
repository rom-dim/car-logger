cmake_minimum_required(VERSION 2.8)

project(car-logger)

file(GLOB SOURCES
    *.h
    *.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
