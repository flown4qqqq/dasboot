# source:

set(HEADERS container.hpp)
set(SOURCES container.cpp)
add_library(container ${SOURCES} ${HEADERS})
apply_compile_flags(container)

target_link_libraries(
    container
    PUBLIC
    cru
)

# tests:

add_executable(isolate isolate.cpp)
apply_compile_flags(isolate)

target_link_libraries(
    isolate
    PRIVATE
    container
)

add_executable(container_ut container_ut.cpp)
apply_compile_flags(container_ut)

target_link_libraries(
    container_ut
    PRIVATE
    GTest::gtest
    container
)

gtest_discover_tests(container_ut)
