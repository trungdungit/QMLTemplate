find_package(Qt5 REQUIRED COMPONENTS Core Qml)

add_library(QmlControls STATIC
    	QmlPalette.cpp
    	QmlPalette.h
	QmlGlobal.cpp
	QmlGlobal.h
	QmlObjectListModel.cpp
	QmlObjectListModel.h

)

target_link_libraries(QmlControls
	PUBLIC
		qml
		FactSystem
		api
		Utilities
		Settings
)

target_include_directories(QmlControls PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
