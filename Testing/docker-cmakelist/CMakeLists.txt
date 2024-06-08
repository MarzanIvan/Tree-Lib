# BUILD_TESTING variable is created by include(CTest)
# It is set to ON by default
if (BUILD_TESTING)
    cmake_minimum_required(VERSION 3.27)
    add_executable(my_test testing.cxx)
    target_link_libraries(my_test PRIVATE GTest::gtest_main)
    include_directories(../)
    include(GoogleTest)
    # Finds all the Google tests associated with the executable
    gtest_discover_tests(my_test)
endif()