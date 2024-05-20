find_package(Qt5 REQUIRED COMPONENTS Core)

add_library(api STATIC
	QMLCorePlugin.cpp
	QMLOptions.cpp
	QMLSettings.cpp
	QmlComponentInfo.cpp
)
target_link_libraries(api
	PUBLIC
		qml
)

target_include_directories(api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

