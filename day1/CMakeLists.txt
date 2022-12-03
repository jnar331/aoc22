
add_executable(day1_1 day1_1.c)
add_executable(day1_2 day1_2.c)

configure_file(${CMAKE_SOURCE_DIR}/day1/input ${CMAKE_BINARY_DIR}/day1 COPYONLY)