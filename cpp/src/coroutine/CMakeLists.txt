set(SOURCE main.cpp)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/3rdparty/benchmark/build)
# set(benchmark_DIR ${PROJECT_SOURCE_DIR}/3rdparty/benchmark/build)

find_package(fmt  REQUIRED)
add_executable(coroutine ${SOURCE})

target_include_directories(coroutine PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(coroutine fmt::fmt)
set_target_properties(coroutine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)