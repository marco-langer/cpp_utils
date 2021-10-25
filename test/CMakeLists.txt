set(TEST_NAME cpp_utils)

set(TEST_SOURCES
    algorithm.cpp
    integer_literals.cpp
    functional.cpp
    main.cpp
    narrow_cast.cpp
    string_utils.cpp
    traits.cpp
)

add_executable(${TEST_NAME} ${TEST_SOURCES})

set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${TEST_NAME} PROPERTY CXX_EXTENSIONS OFF)

target_compile_options(${TEST_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -Werror -Wpedantic -Wundef -Wpointer-arith -Wno-long-long
        -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused
        -Woverloaded-virtual -Wconversion -Wsign-conversion -Wdouble-promotion
        -Wformat=2 -Wduplicated-cond -Wduplicated-branches
        -Wlogical-op -Wuseless-cast>
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX>)

if(WITH_ASAN)
    target_compile_options(${TEST_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
            -fsanitize=address>
        $<$<CXX_COMPILER_ID:MSVC>:
            /fsanitize=address>)
endif()

if(WITH_UBSAN)
    target_compile_options(${TEST_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
            -fsanitize=undefined>)
endif()

target_include_directories(${TEST_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

target_compile_definitions(${TEST_NAME}
    PRIVATE
        BOOST_UT_DISABLE_MODULES)

add_test(${TEST_NAME} ${TEST_NAME})
