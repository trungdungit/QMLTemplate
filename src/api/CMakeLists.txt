find_package(Qt5 REQUIRED COMPONENTS Core)

add_library(api STATIC
	QMLCorePlugin.cpp
	QMLCorePlugin.h
	QMLOptions.cpp
	QMLOptions.h
	QMLSettings.cpp
	QMLSettings.h
	QmlComponentInfo.cpp
	QmlComponentInfo.h
)
target_link_libraries(api
	PUBLIC
		qml
)

target_include_directories(api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

