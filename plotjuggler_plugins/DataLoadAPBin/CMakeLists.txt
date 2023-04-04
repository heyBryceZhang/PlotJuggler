
include_directories(../)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)


message(STATUS "find DataLoadAPBin")





add_library(DataAPBin SHARED
    dataload_apbin.cpp
    dataload_apbin.h
    logformat.h)

target_link_libraries(DataAPBin
    plotjuggler_base
    QCodeEditor)

install(
    TARGETS
        DataAPBin
    DESTINATION
        ${PJ_PLUGIN_INSTALL_DIRECTORY}  )


