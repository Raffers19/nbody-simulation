cmake_minimum_required(VERSION 3.20)

project(NBodySimulation LANGUAGES CXX)

# Create the static physics library
add_library(nbody_physics STATIC
    gravity.cpp
    verlet.cpp
    energy.cpp
)

# Make the library's headers available
target_include_directories(nbody_physics PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Require C++20 for the library and its users
target_compile_features(nbody_physics PUBLIC cxx_std_20)

# Create the executable
add_executable(nbody
    nbody.cpp
)

# Link the physics library to the executable
target_link_libraries(nbody PRIVATE nbody_physics)

# Compiler-specific options
if(MSVC)
    target_compile_options(nbody_physics PRIVATE /W4 /EHsc)
    target_compile_options(nbody PRIVATE /W4 /EHsc)
endif()

#CTest
#Gravity test
enable_testing()

add_executable(test_gravity
    tests/test_gravity.cpp
)

target_link_libraries(test_gravity PRIVATE nbody_physics)

add_test(
    NAME GravityForce
    COMMAND test_gravity
)

#Verlet test
add_executable(test_verlet
    tests/test_verlet.cpp
)

target_link_libraries(test_verlet PRIVATE nbody_physics)

add_test(
    NAME VerletConvergence
    COMMAND test_verlet
)