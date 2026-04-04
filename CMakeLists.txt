cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(PROJECT_NAME FreakSystemMonitor)
project(${PROJECT_NAME})

set(INCLUDE_FILES
    includes/main_window.hpp
)

set(SOURCE_FILES
    source/main_window.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${INCLUDE_FILES} ${SOURCE_FILES} main.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${INCLUDE_FILES} ${SOURCE_FILES} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE _UNICODE)
target_link_libraries(${PROJECT_NAME} PRIVATE user32 gdi32)
