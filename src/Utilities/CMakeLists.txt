find_package(Qt5 REQUIRED COMPONENTS Core Network Positioning Qml)

add_library(Utilities STATIC
    JsonHelper.cpp
    QMLUtilities.cpp
    QMLLoggingCategory.cpp
)

if(MOBILE)
	target_sources(Utilities
		PRIVATE
			MobileScreenMgr.cpp
			MobileScreenMgr.h
	)
endif()

target_link_libraries(Utilities
	PRIVATE
		Qt5::Qml
		qml
	PUBLIC
		Qt5::Core
		Qt5::Positioning
		Qt5::Network
)

target_include_directories(Utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
