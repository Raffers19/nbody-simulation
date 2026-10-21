
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

# Momentum test
add_executable(test_momentum test_momentum.cpp)

target_link_libraries(test_momentum
    PRIVATE nbody_physics
)

add_test(
    NAME MomentumConsistency
    COMMAND test_momentum
)

# Microsoft compiler warnings
if(MSVC)
    target_compile_options(test_gravity PRIVATE /W4 /EHsc)
    target_compile_options(test_verlet PRIVATE /W4 /EHsc)
    target_compile_options(test_momentum PRIVATE /W4 /EHsc)
endif()
