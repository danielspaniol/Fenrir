add_executable(fenrir-gui
    src/main
)
target_include_directories(fenrir-gui PUBLIC
    ../fenrir-core/include
    ../fenrir-ai/include
)
target_link_libraries(fenrir-gui PUBLIC
    fenrir-core
    fenrir-ai
)

if(FENRIR_TESTS)
    add_executable(fenrir-gui-tests
        test/main
    )
    target_include_directories(fenrir-gui-tests PRIVATE
        ../fenrir-core/include
        ../fenrir-ai/include
    )
    target_link_libraries(fenrir-gui-tests PRIVATE
        fenrir-ai
        fenrir-core
        gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(fenrir-gui-tests)
endif(FENRIR_TESTS)


