
cmake_minimum_required(VERSION 3.12)

project(VigilanteGame VERSION "0.0.0.0")


file(GLOB_RECURSE SOURCES "*.cpp" "*.cxx" "*.cc")
file(GLOB_RECURSE RESOURCES "*.qrc")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS *.ui)
set(SRCS ${SOURCES} ${HEADERS} ${RESOURCES} ${FORMS})
source_group(TREE ${CMAKE_SOURCE_DIR}/src/app FILES ${SRCS})

add_executable(VigilanteGame WIN32 ${SRCS})

include_directories("engine")
include_directories("entity")
include_directories("game")
include_directories("gui")


target_link_libraries(
    VigilanteGame
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Concurrent
    Qt5::Network
    Qt5::Xml
    Qt5::Multimedia
    Tadpole
    QXlsx
    )
