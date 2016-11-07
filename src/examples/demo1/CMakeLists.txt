file(GLOB_RECURSE EXECUTABLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc Screen/*.cc)

include_directories("${CMAKE_SOURCE_DIR}/include")
add_executable(demo1 main.cc)

target_link_libraries(demo1 Boiler2D)
