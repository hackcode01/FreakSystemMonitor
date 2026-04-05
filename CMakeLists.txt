cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(PROJECT_NAME FreakSystemMonitor)
project(${PROJECT_NAME})

set(INCLUDE_FILES
    app/defines.hpp

    app/includes/application.hpp
    app/includes/process.hpp
    app/includes/thread.hpp

    app/includes/window.hpp
)

set(SOURCE_FILES
    app/run_program.cpp

    app/source/application.cpp
    app/source/process.cpp
    app/source/thread.cpp

    app/source/window.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${INCLUDE_FILES} ${SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${INCLUDE_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE _UNICODE)
target_link_libraries(${PROJECT_NAME} PRIVATE user32 gdi32)
