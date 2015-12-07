aux_source_directory(. SRC_LIST)

add_library(testplugin SHARED ${SRC_LIST})
target_link_libraries(testplugin common)

