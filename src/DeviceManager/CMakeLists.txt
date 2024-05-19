find_package(Qt5 REQUIRED COMPONENTS Core)

add_library(DeviceManager STATIC
	DeviceManager.cpp
	DeviceManager.h
)

target_link_libraries(DeviceManager
	PUBLIC
		Qt5::Core
		qml
		QmlControls
)

target_include_directories(DeviceManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
