cmake_minimum_required(VERSION 3.10.0)

set(PROJECT_NAME "Monitor")
project(${PROJECT_NAME}
        LANGUAGES CXX)

find_package(PahoMqttCpp REQUIRED)
if(PahoMqttCpp_FOUND)
    message(STATUS "---- PahoMqttCpp IMPORTED ----")
    message(STATUS "PahoMqttCpp_VERSION: ${PahoMqttCpp_VERSION}")
else()
    message(STATUS "PahoMqttCpp couldn't be find")
endif()


add_subdirectory("device-gateway")
add_subdirectory("device")
