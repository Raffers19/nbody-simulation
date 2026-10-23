
# Gravitational force test
add_executable(test_gravity
    test_gravity.cpp
)

target_link_libraries(test_gravity PRIVATE nbody_physics)

add_test(
    NAME GravityForce
    COMMAND test_gravity
)

# Velocity-Verlet convergence test
add_executable(test_verlet
    test_verlet.cpp
)

target_link_libraries(test_verlet PRIVATE nbody_physics)

add_test(
    NAME VerletConvergence
    COMMAND test_verlet
)

# Parallel Velocity-Verlet convergence test
add_executable(test_verlet_parallel
    test_verlet_parallel.cpp
)

target_link_libraries(test_verlet_parallel PRIVATE nbody_physics)

add_test(
    NAME VerletConvergenceParallel
    COMMAND test_verlet_parallel
)

# Momentum test
add_executable(test_momentum test_momentum.cpp)

target_link_libraries(test_momentum
    PRIVATE nbody_physics
)

add_test(
    NAME MomentumConsistency
    COMMAND test_momentum
)

# simulation test
add_executable(test_simulation test_simulation.cpp)

target_link_libraries(test_simulation
    PRIVATE nbody_physics
)

add_test(
    NAME simulationConsistency
    COMMAND test_simulation
)




# Microsoft compiler warnings
if(MSVC)
    target_compile_options(test_gravity PRIVATE /W4 /EHsc)
    target_compile_options(test_verlet PRIVATE /W4 /EHsc)
    target_compile_options(test_momentum PRIVATE /W4 /EHsc)
    target_compile_options(test_simulation PRIVATE /W4 /EHsc)
    target_compile_options(test_verlet_parallel PRIVATE /W4 /EHsc)
endif()
