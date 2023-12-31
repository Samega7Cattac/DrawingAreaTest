# Defines the minimal version allowed of cmake
cmake_minimum_required (VERSION 3.20)

# Set the C++ standard to c++20
set (CMAKE_CXX_STANDARD 20
     CACHE STRING "C++ Standard version")

# Name of the package
set (TARGET_NAME "test_drawingarea"
     CACHE STRING "Name of the target executable" FORCE)

project (${TARGET_NAME})

# Set to "ON" to debug makefile commands
set (CMAKE_VERBOSE_MAKEFILE ON
     CACHE BOOL "Show makefiles commands on build")

add_executable(${TARGET_NAME}
    main.cpp
    MainWindow.cpp MainWindow.hh
    BlockArea.cpp BlockArea.hh
    NodeSelector.cpp NodeSelector.hh)

target_compile_options(${TARGET_NAME}
    PRIVATE
        -Werror -Wall -Wextra)

find_package (PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

# Adds several directories to the include path
target_include_directories (${TARGET_NAME}
    PRIVATE
        ${GTKMM_INCLUDE_DIRS})

# Links the libs
target_link_libraries (${TARGET_NAME}
    PRIVATE
        ${GTKMM_LIBRARIES})

 # Adds flags to the compiler
target_compile_options (${TARGET_NAME}
    PUBLIC
        ${GTKMM_OTHER})

add_subdirectory(images)