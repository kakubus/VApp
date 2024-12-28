cmake_minimum_required(VERSION 3.16)

project(SQL_PoC LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(GTest REQUIRED)

add_executable(SQL_PoC
  main.cpp
  sqlworker.h sqlworker.cpp
  ISqlWorker.h
  tst_base.cpp
)
target_link_libraries(SQL_PoC Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(SQL_PoC gtest gmock)

include(GNUInstallDirs)
install(TARGETS SQL_PoC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Dodaj testy do projektu
add_test(NAME SQL_PoC COMMAND Base)
# Ustawienie uruchamiania testów po kompilacji
add_custom_command(
    TARGET SQL_PoC
    POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
)
add_subdirectory(SQL_Tests)
