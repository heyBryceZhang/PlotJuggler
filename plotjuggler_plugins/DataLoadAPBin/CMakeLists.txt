
include_directories(../)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)


message(STATUS "find DataLoadAPBin")


QT5_WRAP_UI ( UI_SRC
    apbinlog.ui)


add_library(DataAPBin SHARED
    dataload_apbin.cpp
    dataload_apbin.h
    logwidget.h
    logformat.h
     ${UI_SRC})

target_link_libraries(DataAPBin
    plotjuggler_base
    QCodeEditor)

install(
    TARGETS
        DataAPBin
    DESTINATION
        ${PJ_PLUGIN_INSTALL_DIRECTORY}  )
