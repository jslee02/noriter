# Compile each test file
message(STATUS "")
message(STATUS "[ Tests - experiments ]")
file(GLOB tests "*_TEST.cpp")

foreach(test ${tests})

  # Get the name (i.e. bla.cpp => bla)
  get_filename_component(base ${test} NAME_WE)
  add_executable(${base}-experiment ${test})
  if(MSVC)
    target_link_libraries(${base}-experiment ${PROJECT_NAME} optimized gtest debug gtestd)
  else()
    target_link_libraries(${base}-experiment ${PROJECT_NAME} gtest)
  endif()

  set_target_properties(${base}-experiment PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/experiments")

  # Add the executable if not to be ignored
  list_contains(contains ${base} ${dontTest})
  if(NOT contains)
    add_test(${base} ${CMAKE_BINARY_DIR}/bin/tests/experiments/${base})
    message(STATUS "Adding test: " ${base})
  endif(NOT contains)

endforeach(test)

