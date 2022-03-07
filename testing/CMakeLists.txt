
enable_testing()

find_package(GTest REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/testing
    ${CMAKE_SOURCE_DIR}/nngr
    ${GTEST_INCLUDE_DIRS}
)

set(NNGR_TESTS_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/nanogram_tests.cpp
)

add_executable(nonogrammer_tests main.cpp)

target_link_libraries(nonogrammer_tests
    ${NNGR_TESTS_SRC}
    ${GTEST_LIBRARIES}
    pthread
)