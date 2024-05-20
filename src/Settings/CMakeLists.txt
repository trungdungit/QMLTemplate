find_package(Qt5 REQUIRED COMPONENTS Core)

add_library(Settings STATIC
	AppSettings.cpp
	UnitsSettings.cpp
	SettingsGroup.cpp
	SettingsManager.cpp
)

target_link_libraries(Settings
	PUBLIC
		qml
)

target_include_directories(Settings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
