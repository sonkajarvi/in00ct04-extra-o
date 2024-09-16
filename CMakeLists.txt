cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(tests)

add_executable(tests
    main.c
    test_vector.c
    vector.c
)

add_test(
    NAME tests
    COMMAND tests
)
