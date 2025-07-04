cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(cpp_calculator LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(wxBUILD_SHARED OFF)

message(STATUS "Fetching wxWidgets...")

FetchContent_Declare(
   wxWidgets
   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
   GIT_TAG v3.3.0   # LATEST PRE-RELEASE
   GIT_SHALLOW ON
)
FetchContent_MakeAvailable(wxWidgets)

set(MAIN_FILE ./main.cpp)

add_executable(main WIN32 ${MAIN_FILE})

target_sources(main
PRIVATE
   ${MAIN_FILE}

   ./src/ButtonGrid.cpp
   ./src/TextControl.cpp
   ./src/CalculatorButton.cpp

   ./src/ButtonGrid.h
   ./src/TextControl.h
   ./src/CalculatorButton.h
   ./src/constants/Colors.h
   ./src/constants/Buttons.h
)

target_include_directories(main
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/)

target_link_libraries(main PRIVATE wxcore wxnet)
