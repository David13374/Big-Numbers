add_library(BigNumbers "Big-Numbers.cpp" "Big-Numbers.h")
add_library(BigNumbers::BigNumbers ALIAS BigNumbers)

target_include_directories(BigNumbers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(BigNumbers PUBLIC cxx_std_20)


# TODO: Add tests and install targets if needed.
