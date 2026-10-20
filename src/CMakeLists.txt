
# Build the reusable physics library
add_library(nbody_physics STATIC
    gravity.cpp
    verlet.cpp
    energy.cpp
)

# Make headers available to the library
# and to executables linking against it
target_include_directories(nbody_physics PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Build the simulation executable
add_executable(nbody
    nbody.cpp
)

# Link the simulation to the physics library
target_link_libraries(nbody PRIVATE nbody_physics)

# Microsoft compiler options
if(MSVC)
    target_compile_options(nbody_physics PRIVATE /W4 /EHsc)
    target_compile_options(nbody PRIVATE /W4 /EHsc)
endif()
