set(TARGET_NAME "device")
set(TARGET_VERSION "0.1")

set(SOURCES_SERVER 
        "main.cpp"
)

add_executable(${TARGET_NAME} ${SOURCES_SERVER})
target_compile_options(${TARGET_NAME} PRIVATE -Wall)

project(${TARGET_NAME}
        VERSION ${TARGET_VERSION}
        LANGUAGES CXX)

set_target_properties(${TARGET_NAME}
PROPERTIES
    CXX_STANDARD 17
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
        ""
    PRIVATE 
        paho-mqttpp3
        paho-mqtt3as
)


