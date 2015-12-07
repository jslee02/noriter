set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage")

# Create a macro to check if a list contains a value
macro(list_contains var value)
  set(${var})
  foreach (value2 ${ARGN})
    if(${value} STREQUAL ${value2})
      set(${var} true)
    endif (${value} STREQUAL ${value2})
  endforeach (value2)
endmacro(list_contains)

# Include and link to gtest
include_directories(${CMAKE_SOURCE_DIR}/tests/gtest/include)
include_directories(${CMAKE_SOURCE_DIR}/tests/gtest)
add_library(gtest STATIC gtest/src/gtest-all.cc)
add_library(gtest_main STATIC gtest/src/gtest_main.cc)
target_link_libraries(gtest_main gtest)
if(NOT WIN32)
  target_link_libraries(gtest pthread)
endif()
set_target_properties(gtest PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compile each test file
message(STATUS "")
message(STATUS "[ Tests ]")
file(GLOB tests "*_TEST.cpp")

foreach(test ${tests})

  # Get the name (i.e. bla.cpp => bla)
  get_filename_component(base ${test} NAME_WE)
  add_executable(${base} ${test})
  if(MSVC)
    target_link_libraries(${base} ${PROJECT_NAME} optimized gtest debug gtestd)
  else()
    target_link_libraries(${base} ${PROJECT_NAME} gtest)
  endif()

  set_target_properties(${base} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests")

  # Add the executable if not to be ignored
  list_contains(contains ${base} ${dontTest})
  if(NOT contains)
    add_test(${base} ${CMAKE_BINARY_DIR}/bin/tests/${base})
    message(STATUS "Adding test: " ${base})
  endif(NOT contains)

endforeach(test)

add_subdirectory(experiments)
