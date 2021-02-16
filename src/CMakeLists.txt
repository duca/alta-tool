set(TS_FILES AltaTool_pt_BR.ts)

include_directories(AltaTool ${PROJECT_SOURCE_DIR}/include)

add_executable(AltaTool
    altaprinter.hpp
    altaprinter.cpp
    main.cpp
    mainWindow.ui
    mainWindow.hpp
    mainWindow.cpp
    serialWidget.ui
    serialWidget.hpp
    serialWidget.cpp
    serialManager.ui
    serialManager.hpp
    serialManager.cpp
    serial.cpp
    serial.hpp
    stateMachine.cpp
    stateMachine.hpp
    #${PROJECT_SOURCE_DIR}/${TS_FILES}
)

target_link_libraries(AltaTool PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::SerialPort)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

install(TARGETS AltaTool DESTINATION ".")
