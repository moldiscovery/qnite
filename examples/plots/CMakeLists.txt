project(plots)

find_package(
    Qt6
COMPONENTS
    Quick
REQUIRED
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(
    plots
    main.cpp

    plots.qrc
)

target_compile_features(
    plots
PUBLIC
    cxx_std_14
)

target_link_libraries(
    plots
PRIVATE
    qnite
    Qt::Quick
)

target_include_directories(
    plots
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
