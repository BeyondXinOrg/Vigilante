
cmake_minimum_required(VERSION 3.12)

project(HeroEditor VERSION "0.0.0.0")


file(GLOB_RECURSE SOURCES "*.cpp" "*.cxx" "*.cc")
file(GLOB_RECURSE RESOURCES "*.qrc")
file(GLOB_RECURSE HEADERS "*.h" "*.hpp")
file(GLOB_RECURSE FORMS *.ui)
set(SRCS ${SOURCES} ${HEADERS} ${RESOURCES} ${FORMS})
source_group(TREE ${CMAKE_SOURCE_DIR}/src/hero_editor FILES ${SRCS})

add_executable(HeroEditor WIN32 ${SRCS})
target_link_libraries(
    HeroEditor
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Concurrent
    Qt5::Network
    Qt5::Xml
    Tadpole
    QXlsx
    )
