set(TEST_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/catch_config.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Vector3d_test.cpp
        )

add_executable(test
        ${TEST_SOURCE})

target_include_directories(test
        PUBLIC
        ${PROJECT_SOURCE_DIR}/deps
        ${PROJECT_SOURCE_DIR}/src
        )