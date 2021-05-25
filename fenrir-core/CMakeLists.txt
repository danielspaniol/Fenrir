set(FENRIR_CORE_SRC
    src/prelude.cpp
    src/model/color.cpp
    src/model/coord.cpp
)

set(FENRIR_CORE_TEST_SRC
    test/model/color_test.cpp
    test/model/coord_test.cpp
)

add_library(fenrir-core ${FENRIR_CORE_SRC})
target_include_directories(fenrir-core PUBLIC
    include
)

if(FENRIR_TESTS)
    add_executable(fenrir-core-tests ${FENRIR_CORE_TEST_SRC})
    target_include_directories(fenrir-core-tests PRIVATE
        include
    )
    target_link_libraries(fenrir-core-tests PRIVATE
        fenrir-core
        gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(fenrir-core-tests)
endif(FENRIR_TESTS)