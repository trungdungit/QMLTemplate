find_package(Qt5 REQUIRED COMPONENTS Core Qml)

add_library(QmlControls STATIC
    	QmlPalette.cpp
		QmlGlobal.cpp
		QmlObjectListModel.cpp
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
