add_library(qmlunittest
	STATIC
		UnitTest.cpp
		MainWindowTest.cpp
)

target_link_libraries(qmlunittest
	PUBLIC
		qml
		Qt5::Test
)

target_include_directories(qmlunittest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
