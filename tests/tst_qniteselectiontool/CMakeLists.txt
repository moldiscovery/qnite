find_package(
    Qt6
COMPONENTS
    Test
REQUIRED
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(
    tst_qniteselectiontool
    tst_qniteselectiontool.cpp
)

target_link_libraries(
    tst_qniteselectiontool
PRIVATE
    qnite
    Qt::Test
)

add_test(
    tst_qniteselectiontool
    tst_qniteselectiontool
)
