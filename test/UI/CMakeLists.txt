find_package(Qt5 REQUIRED COMPONENTS Core Qml)

add_custom_target(UITest
	SOURCES
		TestWindow.qml
)
