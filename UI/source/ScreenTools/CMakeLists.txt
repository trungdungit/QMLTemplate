find_package(Qt5 REQUIRED COMPONENTS Core Qml)

add_custom_target(ScreenToolsQml
	SOURCES
		RegExpTools.qml
		ScreenTools.qml
		UIConstants.qml
)

