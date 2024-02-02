cmake_minimum_required(VERSION 3.16)

add_custom_target(
    examples
DEPENDS
    line
    plots
)

add_subdirectory(line)
add_subdirectory(plots)
