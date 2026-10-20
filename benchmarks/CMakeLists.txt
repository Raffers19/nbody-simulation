add_executable(benchmark_nbody
    benchmark_nbody.cpp
)

target_link_libraries(benchmark_nbody PRIVATE nbody_physics)

if(MSVC)
    target_compile_options(benchmark_nbody PRIVATE /W4 /EHsc)
endif()