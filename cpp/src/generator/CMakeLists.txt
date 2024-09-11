set(SOURCE main.cpp)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/3rdparty/benchmark/build)
# set(benchmark_DIR ${PROJECT_SOURCE_DIR}/3rdparty/benchmark/build)

find_package(fmt  REQUIRED)
add_executable(generator ${SOURCE})

target_include_directories(generator PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(generator fmt::fmt)
set_target_properties(generator PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)