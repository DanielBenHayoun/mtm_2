cmake_minimum_required(VERSION 3.10)
project(mtm_2)

set(CMAKE_C_STANDARD 99)

set(GCC "-std=c99 -Wall -pedantic-errors -Werror ")
add_definitions(${GCC})


add_executable(ex2_test Tests/test1.c
        Sources/Course.c
        Sources/CourseSystem.c
        Sources/HelperFuncs.c
        Sources/DynamicArray.c

        )

add_executable(Course_test Tests/Course_test.c
        Sources/Course.c
        Sources/HelperFuncs.c
        Sources/DynamicArray.c
        Sources/CourseSystem.c
        )

add_executable(Dynamic_test Tests/DynamicArray_test.c
        Sources/Course.c
        Sources/DynamicArray.c
        Sources/HelperFuncs.c
        Sources/CourseSystem.c
        )

add_executable(final_test_israel Tests/test1.c
        Sources/Course.c
        Sources/DynamicArray.c
        Sources/CourseSystem.c
        Sources/HelperFuncs.c)


add_executable(CourseSystem_test Tests/CourseSystem_test.c
        Sources/Course.c
        Sources/DynamicArray.c
        Sources/CourseSystem.c
        Sources/HelperFuncs.c)


add_executable(Test2 Tests/test2.c
        Sources/Course.c
        Sources/DynamicArray.c
        Sources/HelperFuncs.c
        Sources/CourseSystem.c)