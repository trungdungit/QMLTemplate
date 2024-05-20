if (QML_BUILD_TESTING)
    add_library(qmltest
        STATIC
            UnitTestList.cpp
	    UnitTest.qrc
    )

    add_custom_target(check
        COMMAND ctest --output-on-failure .
        USES_TERMINAL
    )

    function(add_qml_test test_name)
        add_test(
                NAME ${test_name}
                COMMAND $<TARGET_FILE:QMLTemplate> --unittest:${test_name}
        )
        add_dependencies(check QMLTemplate)
    endfunction()

    add_subdirectory(DeviceManager)
    add_subdirectory(qmlunittest)   

    target_link_libraries(qmltest
        PUBLIC
            DeviceManagerTest
            qmlunittest
    )
endif ()
