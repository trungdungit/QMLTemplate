find_package(Qt5 REQUIRED COMPONENTS Core Qml)

add_library(FactSystem STATIC
	Fact.cpp
	Fact.h
	FactGroup.cpp
	FactGroup.h
	FactMetaData.cpp
	FactMetaData.h
	FactSystem.cpp
	FactSystem.h
	FactValueSliderListModel.cpp
	FactValueSliderListModel.h
	SettingsFact.cpp
	SettingsFact.h
)

target_link_libraries(FactSystem
	PUBLIC
		qml
)

target_include_directories(FactSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
