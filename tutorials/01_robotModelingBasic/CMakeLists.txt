aux_source_directory(. SRC_LIST)

add_executable(01_robotModelingBasic ${SRC_LIST})
target_link_libraries(01_robotModelingBasic common dynamics engine)

