file(GLOB_RECURSE Boiler2D_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc *.h)

include_directories("${CMAKE_SOURCE_DIR}/include")
add_library(Boiler2D STATIC ${Boiler2D_SRCS})
target_link_libraries(Boiler2D SDL2 SDL2_image SDL2_ttf)
