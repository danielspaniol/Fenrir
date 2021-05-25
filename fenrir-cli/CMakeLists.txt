add_executable(fenrir-cli
    src/main
)
target_include_directories(fenrir-cli PUBLIC
    ../fenrir-core/include
    ../fenrir-ai/include
)
target_link_libraries(fenrir-cli PUBLIC
    fenrir-core
    fenrir-ai
)

if(FENRIR_TESTS)
    add_executable(fenrir-cli-tests
        test/main
    )
    target_include_directories(fenrir-cli-tests PRIVATE
        ../fenrir-core/include
        ../fenrir-ai/include
    )
    target_link_libraries(fenrir-cli-tests PRIVATE
        fenrir-ai
        fenrir-core
    )
endif(FENRIR_TESTS)

