set(TEST_NAME cpp_utils)

set(TEST_SOURCES
    main.cpp
)

add_executable(${TEST_NAME} ${TEST_SOURCES})

if(WITH_ASAN)
    if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
      target_compile_options(${TEST_NAME} PUBLIC -fsanitize=address)
      target_link_options(${TEST_NAME} PUBLIC -fsanitize=address)
    endif()
endif()

target_include_directories(${TEST_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

target_compile_definitions(${TEST_NAME}
    PRIVATE
        BOOST_UT_DISABLE_MODULES)

add_test(${TEST_NAME} ${TEST_NAME})
