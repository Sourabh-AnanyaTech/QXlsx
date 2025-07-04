cmake_minimum_required(VERSION 3.14)
project(TestExcel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

# Find Qt (Core and Gui components are common)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)

# Add the QXlsx library.
# It's located in the parent directory's QXlsx folder.
# Need to ensure this path is correct relative to the build directory, not source.
# If building from /build, and TestExcel is a subdir of the main project being configured,
# then add_subdirectory(../QXlsx) might be from /build/TestExcel back to /build/QXlsx.
# Let's assume we are building from a root build dir, e.g. /app/build
# and the main CMakeLists.txt for the whole project would be in /app/
# and it would add_subdirectory(QXlsx) and add_subdirectory(TestExcel).
# Since I'm creating TestExcel/CMakeLists.txt to be potentially standalone or part of a larger build:
# The path to QXlsx should be relative to this TestExcel/CMakeLists.txt file's location in the source tree.
add_subdirectory(../QXlsx ${CMAKE_CURRENT_BINARY_DIR}/QXlsx_build)


# We need to ensure CMAKE_AUTOMOC is ON for Qt projects
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# List all source files for the TestExcel executable
set(TEST_EXCEL_SOURCES
    main.cpp
    calendar.cpp
    chart.cpp
    chartextended.cpp
    chartsheet.cpp
    datavalidation.cpp
    definename.cpp
    demo.cpp
    documentproperty.cpp
    extractdata.cpp
    formulas.cpp
    hello.cpp
    hyperlinks.cpp
    image.cpp
    mergecells.cpp
    numberformat.cpp
    pageMargins.cpp
    readStyle.cpp
    richtext.cpp
    rowcolumn.cpp
    style.cpp
    worksheetoperations.cpp
    xychart.cpp
)

add_executable(TestExcel ${TEST_EXCEL_SOURCES})

# Link TestExcel against QXlsx
target_link_libraries(TestExcel PRIVATE QXlsx::QXlsx Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)

# Include current directory for headers if main.cpp includes others directly
target_include_directories(TestExcel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
