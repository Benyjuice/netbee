#aux_source_directory(../core CORE_SRC)
add_executable(netbee_client client.c ${CORE_SRC})
install(TARGETS netbee_client DESTINATION bin)
