set(SOURCE random_number.cpp main.cpp)

add_executable(random_number ${SOURCE})

target_include_directories(random_number PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_target_properties(random_number PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)