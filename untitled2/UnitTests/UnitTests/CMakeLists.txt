# cmake_minimum_required(VERSION 3.16)

# project(ClassesTests LANGUAGES CXX)

# enable_testing()

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

# add_executable(ClassesTests main.cpp tst_classestests.cpp
#                 )

# add_test(NAME ClassesTests COMMAND ClassesTests)

# target_link_libraries(ClassesTests PRIVATE GTest::GTest Qt6::Quick)
# if (GMock_FOUND)
#     target_link_libraries(ClassesTests INTERFACE GTest::GMock)
# endif()

add_library(untitled2 -L ../../)

add_executable(UnitTests main.cpp)

target_link_libraries(untitled2 OBJECT appuntitled2)

add_test(
  NAME
    UnitTest
  COMMAND
    $<TARGET_FILE:untitled2>
  )

