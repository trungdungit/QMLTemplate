find_package(Qt5 REQUIRED COMPONENTS Core)

add_library(Settings STATIC
	AppSettings.cpp
	AppSettings.h
	UnitsSettings.cpp
	UnitsSettings.h
	SettingsGroup.cpp
	SettingsGroup.h
	SettingsManager.cpp
	SettingsManager.h
)

target_link_libraries(Settings
	PUBLIC
		qml
)

target_include_directories(Settings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
