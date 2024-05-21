add_subdirectory(source)

find_package(Qt5 REQUIRED COMPONENTS Core Qml)

add_custom_target(uiQml
	SOURCES
		MainWindow.qml
)
