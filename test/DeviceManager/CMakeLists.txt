add_library(DeviceManagerTest
	STATIC
		DeviceManagerTest.cpp 
)

target_link_libraries(DeviceManagerTest
	PUBLIC
		qml
		qmlunittest
)

target_include_directories(DeviceManagerTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
