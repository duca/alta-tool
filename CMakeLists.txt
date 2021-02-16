cmake_minimum_required(VERSION 3.11)

project(AltaTool LANGUAGES CXX)

# Point CMake to the custom modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# It would be nice if CMake offered a constant for Linux
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX 1)
endif()

set(PROJECT_NAME "AltaTool")
set(PROJECT_DESCRIPTION "Silhouette Alta calibration and filament replacement stand alone tool")
set(PROJECT_AUTHOR "Eduardo Lopes")
set(PROJECT_URL "")

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (UNIX)
list(APPEND CMAKE_MODULE_PATH "/opt/qt5/lib64/cmake/")
endif (UNIX)

find_package(QT NAMES Qt5 COMPONENTS Widgets LinguistTools SerialPort REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools SerialPort REQUIRED)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#add_subdirectory(3rdparty/cpp-httplib)
add_subdirectory(src)


include(InstallRequiredSystemLibraries)

if (WIN32)
  include(Windeployqt)
  WindeployQt(COMPILER_RUNTIME TRUE FORCE TRUE TARGET AltaTool)
endif()

set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CMAKE_PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VENDOR "Oceaneering")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")

# if(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full UNIX paths properly.
  # Make sure there is at least one set of four backlashes.
  # set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
  # set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
  # set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} My Famous Project")
  # set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
  # set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
  # set(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
  # set(CPACK_NSIS_MODIFY_PATH ON)
# else()
#   set(CPACK_STRIP_FILES "bin/MyExecutable")
#   set(CPACK_SOURCE_STRIP_FILES "")
# endif()
set(CPACK_PACKAGE_EXECUTABLES "AltaTool" "My Executable")

include(CPack)
