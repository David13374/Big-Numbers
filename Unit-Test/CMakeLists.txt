include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(BigNumbersTests test.cpp)

target_link_libraries(BigNumbersTests
    PRIVATE
        BigNumbers::BigNumbers
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(BigNumbersTests)