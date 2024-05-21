if(NOT QML_BUILD_TESTING)
    return()
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Test)

include(CTest)
enable_testing()

add_custom_target(check
    COMMAND ctest --output-on-failure .
    USES_TERMINAL
)

function(add_qml_test test_name)
    add_test(
        NAME ${test_name}
        COMMAND $<TARGET_FILE:${PROJECT_NAME}> --unittest:${test_name}
    )
    add_dependencies(check ${PROJECT_NAME})
endfunction()

add_subdirectory(DeviceManager)
add_subdirectory(qmlunittest)

add_qml_test(DeviceManagerTest)
add_qml_test(MainWindowTest)

add_library(qmltest
    STATIC
        UnitTestList.cpp
	    UnitTest.qrc
)

target_link_libraries(qmltest
	PUBLIC
        DeviceManagerTest
        qmlunittest
	    Qt5::Core
)

target_include_directories(qmltest INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
