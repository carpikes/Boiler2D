file(GLOB_RECURSE EXECUTABLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc)

include_directories("${CMAKE_SOURCE_DIR}/include")
add_executable(demo main.cc)

target_link_libraries(demo Boiler2D)
