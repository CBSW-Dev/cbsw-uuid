cmake_minimum_required(VERSION 3.10)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

project(CBSW_Uuid VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (NOT PROJECT_IS_TOP_LEVEL)
  set(CBSW_UUID_INCLUDED True PARENT_SCOPE)
  set(CBSW_UUID_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
endif()

set(CBSW_UUID_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CBSW_UUID_TEST_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(CBSW_UUID_DEPENDENCIES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

# Test

option(CBSW_UUID_BUILD_TESTS "Build the uuid unit test applications" ON)

if(CBSW_UUID_BUILD_TESTS)
  add_executable(cbsw-uuid-test test/main.cpp)

  add_subdirectory(${CBSW_UUID_TEST_DIRECTORY})

  option(CBSW_UNIT_BUILD_EXAMPLES "" OFF)
  option(CBSW_UNIT_EXPECT_BUILD_EXAMPLES "" OFF)

  if(NOT DEFINED CBSW_UNIT_INCLUDED)
    add_subdirectory(${CBSW_UUID_DEPENDENCIES_DIRECTORY}/cbsw-unit cbsw-unit)
  endif()

  if(NOT DEFINED CBSW_UNIT_EXPECT_INCLUDED)
    add_subdirectory(${CBSW_UUID_DEPENDENCIES_DIRECTORY}/cbsw-unit-expect cbsw-unit-expect)
  endif()

  target_precompile_headers(cbsw-uuid-test PRIVATE ${CBSW_UUID_TEST_DIRECTORY}/pch.hpp)
  target_include_directories(cbsw-uuid-test PUBLIC "${CBSW_UUID_TEST_DIRECTORY}")
  target_include_directories(cbsw-uuid-test PUBLIC "${CBSW_UUID_INCLUDE_DIRECTORY}")
  target_include_directories(cbsw-uuid-test PUBLIC "${CBSW_UUID_SOURCE_DIRECTORY}")
  target_include_directories(cbsw-uuid-test PUBLIC "${CBSW_UNIT_EXPECT_INCLUDE_DIRECTORY}")
  target_include_directories(cbsw-uuid-test PUBLIC "${CBSW_UNIT_INCLUDE_DIRECTORY}")

  target_link_libraries(cbsw-uuid-test cbsw-unit-expect cbsw-unit)

  target_compile_options(cbsw-uuid-test PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
  )
endif()

