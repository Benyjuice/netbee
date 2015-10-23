add_executable(netbee_server server.c ${CORE_SRC} ${UTILS_SRC})
install(TARGETS netbee_server DESTINATION bin)
