
cmake_minimum_required(VERSION 3.12)

project(MapEditor VERSION "0.0.0.0")


file(GLOB_RECURSE SOURCES "*.cpp" "*.cxx" "*.cc")
file(GLOB_RECURSE RESOURCES "*.qrc")
file(GLOB_RECURSE HEADERS "*.h" "*.hpp")
file(GLOB_RECURSE FORMS *.ui)
set(SRCS ${SOURCES} ${HEADERS} ${RESOURCES} ${FORMS})
source_group(TREE ${CMAKE_SOURCE_DIR}/src/map_editor FILES ${SRCS})

add_executable(MapEditor WIN32 ${SRCS})
target_link_libraries(
    MapEditor
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Concurrent
    Qt5::Network
    Qt5::Xml
    )
