cmake_minimum_required(VERSION 3.10.1 FATAL_ERROR)

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release")
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if(UNIX)
    find_program(CCACHE_PROGRAM ccache)
    message(STATUS "Using ccache")
    if(CCACHE_PROGRAM)
        set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    endif()
elseif(WIN32)
    if(SCCACHE_PROGRAM)
        message(STATUS "Using sccache")
        set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
        if(MSVC)
            string(APPEND CMAKE_CXX_FLAGS " /FS")
        endif()
    endif()
endif()

#######################################################
#                   Project Info
#######################################################

project(QMLTemplate
    VERSION 1.0
    DESCRIPTION "QMLTemplate"
    HOMEPAGE_URL "https://qmltemplate.com/"
    LANGUAGES C CXX
)

if(UNIX AND NOT APPLE AND NOT ANDROID)
    set(LINUX TRUE)
endif()

if(APPLE AND NOT IOS)
    set(MACOS TRUE)
endif()

if(IOS OR ANDROID)
    set(MOBILE TRUE)
    add_compile_definitions(__mobile__)
endif()

#######################################################
#            CMake Configuration Options
#######################################################

include(FeatureSummary)
include(FetchContent)
include(ExternalProject)
include(GNUInstallDirs)
include(CMakeDependentOption)
include(CMakePrintHelpers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(LINUX)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/AppDir/usr)
else()
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/staging)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR OFF)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

cmake_print_variables(CMAKE_VERSION)
cmake_print_variables(CMAKE_PREFIX_PATH)
cmake_print_variables(CMAKE_HOST_SYSTEM_NAME)
cmake_print_variables(CMAKE_HOST_SYSTEM_VERSION)
cmake_print_variables(CMAKE_SYSTEM_NAME)
cmake_print_variables(CMAKE_SYSTEM_VERSION)
cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)
cmake_print_variables(CMAKE_BUILD_TYPE)
cmake_print_variables(CMAKE_TOOLCHAIN_FILE)

#######################################################
#               Qt5 Configuration
#######################################################

include(Qt5Configuration)

set(QT_QML_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml" CACHE PATH "Install path for QML" FORCE)
set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/UI CACHE STRING "Extra QML import paths" FORCE)
add_compile_definitions(QT_DISABLE_DEPRECATED_UP_TO=0x050F00)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(
        NDEBUG
        QT_NO_DEBUG
        QT_NO_DEBUG_OUTPUT
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(CTest)
    enable_testing()

    set(QT_ENABLE_VERBOSE_DEPLOYMENT ON CACHE BOOL "Verbose Deployment")
endif()

if(ANDROID)
    cmake_print_variables(QT_ANDROID_APPLICATION_ARGUMENTS QT_HOST_PATH)

    set(QT_ENABLE_VERBOSE_DEPLOYMENT ON CACHE BOOL "Verbose Deployment")
    # QT_USE_TARGET_ANDROID_BUILD_DIR
    list(APPEND QT_ANDROID_MULTI_ABI_FORWARD_VARS QML_STABLE_BUILD)
    list(APPEND QT_ANDROID_MULTI_ABI_FORWARD_VARS QT_HOST_PATH)
    cmake_print_variables(QT_ANDROID_MULTI_ABI_FORWARD_VARS)
    # QT_ANDROID_DEPLOY_RELEASE
    # set(QT_ANDROID_DEPLOYMENT_TYPE ON CACHE BOOL "Deployment Type")
    cmake_dependent_option(QT_ANDROID_SIGN_APK "Enable Signing APK" ON "CMAKE_BUILD_TYPE STREQUAL Release" OFF)
    if(QT_ANDROID_SIGN_APK)
        message(STATUS "Signing APK")
        message(STATUS "QT_ANDROID_KEYSTORE_PATH $ENV{QT_ANDROID_KEYSTORE_PATH}")
        message(STATUS "QT_ANDROID_KEYSTORE_ALIAS $ENV{QT_ANDROID_KEYSTORE_ALIAS}")
        # QT_ANDROID_KEYSTORE_STORE_PASS, QT_ANDROID_KEYSTORE_KEY_PASS
    endif()

    if(NOT Qt5LinguistTools_DIR)
        set(Qt5LinguistTools_DIR ${QT_HOST_PATH}/lib/cmake/Qt5LinguistTools)
    endif()
endif()

find_package(Qt5
    REQUIRED
    COMPONENTS
        Core
        Location
        Quick
        QuickControls2
        QuickWidgets
        Test
        Widgets
        LinguistTools
    HINTS
        ${QT_LIBRARY_HINTS}
)

#######################################################
#                Options
#######################################################

cmake_dependent_option(QML_BUILD_TESTING "Enable testing" ON "CMAKE_BUILD_TYPE STREQUAL Debug" OFF)
if(QML_BUILD_TESTING)
    add_compile_definitions(UNITTEST_BUILD)
endif()

cmake_dependent_option(QML_DEBUG_QML "Build TemplateProject with QML debugging/profiling support." OFF "CMAKE_BUILD_TYPE STREQUAL Debug" OFF)
if(QML_DEBUG_QML)
    message(STATUS "To enable the QML debugger/profiler, run with: '-qmljsdebugger=port:1234'")
    add_compile_definitions(QT_QML_DEBUG)
endif()

#######################################################
#                Resources
#######################################################

set(QML_RESOURCES
    ${CMAKE_SOURCE_DIR}/qmltemplate.qrc
    ${CMAKE_SOURCE_DIR}/resources.qrc
)

if(QML_BUILD_TESTING)
    list(APPEND QML_RESOURCES ${CMAKE_SOURCE_DIR}/test/UnitTest.qrc)
endif()

if(WIN32)
    list(APPEND QML_RESOURCES ${CMAKE_SOURCE_DIR}/deploy/windows/sample.rc)
endif()

#######################################################
#               QMLTemplate Target
#######################################################

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${QML_RESOURCES}
)

#######################################################
#               Translations
#######################################################   
file(GLOB TS_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/translations/qml_*.ts)
QT5_ADD_TRANSLATION(${PROJECT_NAME} ${TS_SOURCES})

target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)

set_target_properties(${PROJECT_NAME} PROPERTIES QT_RESOURCE_PREFIX "/qml")

if(WIN32)
    set_target_properties(${PROJECT_NAME} 
        PROPERTIES 
            WIN32_EXECUTABLE TRUE
            QT_TARGET_RC_ICONS "${CMAKE_SOURCE_DIR}/deploy/windows/sample.ico"
    )
    add_compile_definitions(_USE_MATH_DEFINES)
elseif(MACOS)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/deploy/mac/MacOSXBundleInfo.plist.in
            MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_COPYRIGHT "Copyright (c) 2018 QGroundControl. All rights reserved."
            MACOSX_BUNDLE_GUI_IDENTIFIER "io.mavlink.qgroundcontrol"
            MACOSX_BUNDLE_ICON_FILE "${CMAKE_SOURCE_DIR}/resources/icons/macx.icns"
            # MACOSX_BUNDLE_INFO_STRING
            # MACOSX_BUNDLE_LONG_VERSION_STRING
            # MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )
elseif(IOS)
    enable_language(OBJC)
    set_target_properties(${PROJECT_NAME} PROPERTIES QT_IOS_LAUNCH_SCREEN ${CMAKE_SOURCE_DIR}/deploy/ios/QGCLaunchScreen.xib)
elseif(ANDROID)
    FetchContent_Declare(android_openssl
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip
    )
    FetchContent_MakeAvailable(android_openssl)
    include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)
    add_android_openssl_libraries(${PROJECT_NAME})

    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            # QT_ANDROID_ABIS ${ANDROID_ABI}
            QT_ANDROID_MIN_SDK_VERSION 26
            QT_ANDROID_TARGET_SDK_VERSION 34
            QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/android
            QT_ANDROID_VERSION_NAME "${CMAKE_PROJECT_VERSION}"
            # QT_ANDROID_VERSION_CODE "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
            QT_QML_ROOT_PATH ${CMAKE_SOURCE_DIR}
    )
    # get_target_property(QML_ANDROID_DEPLOY_FILE ${PROJECT_NAME} QT_ANDROID_DEPLOYMENT_SETTINGS_FILE)
elseif(LINUX)

endif()

include(Git)
add_compile_definitions(
    QML_APPLICATION_NAME="QMLTemplate"
    QML_ORG_NAME="QMLTemplate.org"
    QML_ORG_DOMAIN="org.qmltemplate"
    APP_VERSION_STR="${APP_VERSION_STR}"
)

add_subdirectory(src)
add_subdirectory(UI)
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Widgets
        qml
        QmlControls
        Utilities
)
if(QML_BUILD_TESTING)
    add_subdirectory(test)
    target_link_libraries(${PROJECT_NAME} PRIVATE qmltest)
endif()

#######################################################
#		Install Configuration
#######################################################

install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    BUNDLE  DESTINATION .
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/resources/
    DESTINATION ${CMAKE_INSTALL_DATADIR}/TemplateProject
)
