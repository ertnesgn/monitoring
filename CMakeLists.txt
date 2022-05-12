cmake_minimum_required(VERSION 3.10.0)

set(PROJECT_NAME "Monitor")
project(${PROJECT_NAME}
        LANGUAGES CXX)

add_subdirectory("device-gateway")
add_subdirectory("device")
