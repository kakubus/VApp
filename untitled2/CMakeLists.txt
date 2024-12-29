cmake_minimum_required(VERSION 3.0)

project(untitled2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(GTest REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appuntitled2
    main.cpp
)

qt_add_qml_module(appuntitled2
    URI untitled2
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES vehicle.h vehicle.cpp
        SOURCES carbook.h carbook.cpp
        SOURCES carevent.h carevent.cpp
        SOURCES tst_base.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appuntitled2 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appuntitled2
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appuntitled2
    PRIVATE Qt6::Quick
    Qt6::Quick GTest::gtest
)


include(GNUInstallDirs)
install(TARGETS appuntitled2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
add_test(NAME appuntitled2 COMMAND Base_Tst)
enable_testing()

# add_executable(BaseTestSuite tst_main_app_class_mechanics.cpp)

# # Dodaj testy do projektu
# add_test(NAME appuntitled2 COMMAND BaseTestSuite)
# # Ustawienie uruchamiania testów po kompilacji
# add_custom_command(
#     TARGET appuntitled2
#     POST_BUILD
#     COMMAND ${CMAKE_CTEST_COMMAND} --verbose
# )
enable_testing()

# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# if ($ENV{GOOGLETEST_DIR})
#     get_filename_component(_GTEST_BASE $ENV{GOOGLETEST_DIR} REALPATH)
# elseif (EXISTS "") # set by QC
#     get_filename_component(_GTEST_BASE "" REALPATH) # set by QC
# endif()

# if (NOT GTEST_ROOT)
#     if (_GTEST_BASE)
#         message("Setting GTEST_ROOT to ${_GTEST_BASE}")
#         set(GTEST_ROOT ${_GTEST_BASE})
#     else()
#         message("No GTEST_ROOT specified - using system defaults.")
#     endif()
# endif()

# find_package(GTest REQUIRED)
# if (NOT GTest_FOUND)
#     message (FATAL_ERROR "No GTest Found")
# endif()

# add_executable(ClassTest GTests/main.cpp GTests/tst_classtest.cpp)
# add_test(NAME ClassTest COMMAND ClassTest)

# target_link_libraries(ClassTest PRIVATE GTest::GTest)
# if (GMock_FOUND)
#     target_link_libraries(ClassTest INTERFACE GTest::GMock)
# endif()


#add_subdirectory(UnitTests/UnitTests)
# add_test(NAME UnitTests COMMAND ClassesTests)
# add_executable(UnitTests/UnitTests/main.cpp)
# enable_testing()


