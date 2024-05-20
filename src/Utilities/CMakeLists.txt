find_package(Qt5 REQUIRED COMPONENTS Core Network Positioning Qml)

add_library(Utilities STATIC
    JsonHelper.cpp
    QML.cpp
    QMLLoggingCategory.cpp
)

if(MOBILE)
	target_sources(Utilities
		PRIVATE
			MobileScreenMgr.cpp
        		MobileScreenMgr.h
	)
endif()

set(BUILD_SHAPELIB_CONTRIB OFF CACHE INTERNAL "")
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
set(BUILD_TESTING OFF CACHE INTERNAL "")

target_link_libraries(Utilities
	PRIVATE
		Qt5::Qml
		qml
	PUBLIC
		Qt5::Core
		Qt5::Positioning
		Qt5::Network
)

target_include_directories(Utilities
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)
