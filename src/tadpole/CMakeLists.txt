project(Tadpole)

include_directories("utils")

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Sql Test Xml SerialPort Concurrent Network Multimedia SerialPort)
add_definitions(-DQT_MESSAGELOGCONTEXT)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES "*.cpp" "*.cxx" "*.cc")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE RESOURCES "*.qrc")
file(GLOB_RECURSE FORMS *.ui)
source_group("" FILES ${HEADERS} ${SOURCES})
set(SRCS ${SOURCES} ${HEADERS} ${RESOURCES} ${FORMS})

add_library(${PROJECT_NAME} STATIC ${SRCS})

target_link_libraries(
    ${PROJECT_NAME}
    Qt5::Gui
    Qt5::Widgets
    Qt5::Sql
    Qt5::Xml
    Qt5::Network
    Qt5::Concurrent
    Qt5::SerialPort
    )


