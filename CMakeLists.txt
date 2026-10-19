
cmake_minimum_required(VERSION 3.20)

project(NBodySimulation LANGUAGES CXX)

add_executable(nbody
    nbody.cpp
    gravity.cpp
    verlet.cpp
    energy.cpp
)

set_target_properties(nbody PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if(MSVC)
    target_compile_options(nbody PRIVATE /W4 /EHsc)
endif()
