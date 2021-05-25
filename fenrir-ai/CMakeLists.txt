add_library(fenrir-ai
    dummy.cpp
)
target_include_directories(fenrir-ai PUBLIC
    include
    ../fenrir-core/include
)
target_link_libraries(fenrir-ai PUBLIC
    fenrir-core
)

if(FENRIR_TESTS)
    add_executable(fenrir-ai-tests
        test/main
    )
    target_include_directories(fenrir-ai-tests PRIVATE
        include
    ../fenrir-core/include
    )
    target_link_libraries(fenrir-ai-tests PRIVATE
        fenrir-ai
    )
endif(FENRIR_TESTS)
