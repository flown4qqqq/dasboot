# source:

set(SOURCES controller.cpp)
set(HEADERS controller.hpp)
add_library(controller ${SOURCES} ${HEADERS})
apply_compile_flags(controller)

target_link_libraries(
    controller
    PUBLIC
    ProtobufMessages
    cru
    cppzmq
)

add_dependencies(controller ProtobufMessages)

# tests:

add_executable(controller_ut controller_ut.cpp)
apply_compile_flags(controller_ut)

target_link_libraries(
    controller_ut
    PRIVATE
    GTest::gtest
    controller
    ProtobufMessages
    cppzmq
    cli
)

gtest_discover_tests(controller_ut)
