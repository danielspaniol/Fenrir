add_library(fenrir-core
    dummy.cpp
)
target_include_directories(fenrir-core PUBLIC
    include
)

if(FENRIR_TESTS)
    add_executable(fenrir-core-tests
        test/main
    )
    target_include_directories(fenrir-core-tests PRIVATE
        include
    )
    target_link_libraries(fenrir-core-tests PRIVATE
        fenrir-core
    )
endif(FENRIR_TESTS)