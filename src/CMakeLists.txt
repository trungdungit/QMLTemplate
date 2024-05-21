project(qml)

#######################################################
#             Source Files
#######################################################
add_library(${PROJECT_NAME} STATIC
        CmdLineOptParser.cpp
        CmdLineOptParser.h
        QMLApplication.cpp
        QMLApplication.h
        QMLConfig.h
        QMLToolbox.cpp
        QMLToolbox.h
        RunGuard.cpp
        RunGuard.h
)

# Subdirectories
add_subdirectory(DeviceManager)
add_subdirectory(FactSystem)
add_subdirectory(api)
add_subdirectory(QmlControls)
add_subdirectory(Settings)
add_subdirectory(Utilities)

#######################################################
#               Linking Libraries
#######################################################
target_link_libraries(${PROJECT_NAME}
        PUBLIC
	    Qt5::QuickControls2
            Qt5::QuickWidgets
            Qt5::Widgets

            DeviceManager
            Settings
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(ANDROID)
else()
endif()
