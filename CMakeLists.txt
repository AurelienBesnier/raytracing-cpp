cmake_minimum_required(VERSION 3.20)

project(Raytracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP)
if(NOT OpenMP_CXX_FOUND)
    message(WARNING "failed to find OpenMP")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX -fsigned-char -fexceptions -fopenmp -O0 -g")


add_executable(Raytracing main.cpp)
target_include_directories(Raytracing PRIVATE include)

install(TARGETS Raytracing
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
