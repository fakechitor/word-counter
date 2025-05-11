cmake_minimum_required(VERSION 3.16)

project(word-counter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Test)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql Test)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    wordcountdto.h
    wordcountservice.h
    wordcounthistory.h
)

set(TEST_SOURCES
    tests/test_wordcountservice.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(word-counter
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        database.h
    )
else()
    if(ANDROID)
        add_library(word-counter SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(word-counter
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(word-counter PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

# Добавляем путь к корню проекта для тестов
if(TEST_SOURCES)
    message(STATUS "Configuring unit tests: ${TEST_SOURCES}")

    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(word-counter-tests
            MANUAL_FINALIZATION
            ${TEST_SOURCES}
        )
    else()
        add_executable(word-counter-tests
            ${TEST_SOURCES}
        )
    endif()

    target_link_libraries(word-counter-tests PRIVATE
        Qt${QT_VERSION_MAJOR}::Test
    )

    # Добавляем путь к заголовочным файлам
    target_include_directories(word-counter-tests PRIVATE ${CMAKE_SOURCE_DIR})

    add_test(NAME WordCounterTests COMMAND word-counter-tests)

    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(word-counter-tests)
    endif()
endif()

set_target_properties(word-counter PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS word-counter
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(word-counter)
endif()
