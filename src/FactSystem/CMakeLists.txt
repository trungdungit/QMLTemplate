find_package(Qt5 REQUIRED COMPONENTS Core Qml)

add_library(FactSystem STATIC
	Fact.cpp
	FactGroup.cpp
	FactMetaData.cpp
	FactSystem.cpp
	FactValueSliderListModel.cpp
	SettingsFact.cpp
)

target_link_libraries(FactSystem
	PUBLIC
		qml
)

target_include_directories(FactSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
