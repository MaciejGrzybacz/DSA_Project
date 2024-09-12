cmake_minimum_required(VERSION 3.10)
project(DSA_Project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(dsa_lib "")

function(add_algorithm group name)
    target_sources(dsa_lib PRIVATE src/${group}/${name}.cpp)
    target_include_directories(dsa_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()

## Add algorithms here
add_algorithm(graph weighted_graph)
add_algorithm(graph unweighted_graph)
add_algorithm(sorting sort)
add_algorithm(data_structures union_find)
add_algorithm(data_structures linked_list)
add_algorithm(data_structures stack)
add_algorithm(data_structures queue)
add_algorithm(string algorithms)



include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

function(add_dsa_test group name)
    add_executable(${group}_${name}_test tests/${group}/${name}_test.cpp)
    target_link_libraries(${group}_${name}_test
            dsa_lib
            gtest
            gtest_main
    )
    add_test(NAME ${group}_${name}_test COMMAND ${group}_${name}_test)
endfunction()

## Add tests here
add_dsa_test(graph weighted_graph)
add_dsa_test(graph unweighted_graph)
add_dsa_test(data_structures union_find)
add_dsa_test(data_structures linked_list)
add_dsa_test(data_structures stack)
add_dsa_test(data_structures queue)
add_dsa_test(string algorithms)

enable_testing()