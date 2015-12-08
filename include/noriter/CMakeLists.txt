file(GLOB_RECURSE
    HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hxx)
file(GLOB_RECURSE
    CONFIGURED_HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/*.h
    ${CMAKE_CURRENT_BINARY_DIR}/*.hxx)

set(NORITER_HEADERS ${HEADERS} ${CONFIGURED_HEADERS} PARENT_SCOPE)

# Generate header for this namespace
noriter_get_filename_components(header_names "noriter headers" ${HEADERS})
noriter_generate_include_header_list(
  noriter_headers
  "noriter/"
  "noriter headers"
  ${header_names}
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/noriter.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/noriter.h
)

#file(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" FCL_CONFIG_IN_DIR)
#file(TO_NATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}" FCL_CONFIG_OUT_DIR)
#configure_file("${FCL_CONFIG_IN_DIR}/config.h.in" "${FCL_CONFIG_OUT_DIR}/config.h")
#install(FILES "${FCL_CONFIG_OUT_DIR}/config.h" DESTINATION include/fcl)

