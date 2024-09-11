set(SOURCE main.cpp)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/3rdparty/benchmark/build)
set(benchmark_DIR ${PROJECT_SOURCE_DIR}/3rdparty/benchmark/build)

find_package(benchmark REQUIRED)
add_executable(benchmark_ex ${SOURCE})

target_include_directories(benchmark_ex PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(benchmark_ex benchmark::benchmark)
set_target_properties(benchmark_ex PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)