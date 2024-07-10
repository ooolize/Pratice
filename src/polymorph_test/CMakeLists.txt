set(SOURCE main.cpp)

# set(benchmark_DIR ${PROJECT_SOURCE_DIR}/3rdparty/benchmark/build)

find_package(benchmark REQUIRED)
add_executable(polomorpy_test ${SOURCE})

target_include_directories(polomorpy_test PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(polomorpy_test benchmark::benchmark)
set_target_properties(polomorpy_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)