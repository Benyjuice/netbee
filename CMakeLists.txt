cmake_minimum_required(VERSION 2.8)
project(netbee)
cmake_minimum_required(VERSION 2.8)
add_subdirectory(src bin)
install(FILES COPYRIGHT README DESTINATION share/doc/netbee/server)
install(PROGRAMS runnetbee.sh DESTINATION bin)
install(DIRECTORY doc/ DESTINATION share/doc/netbee/server)
#add_executable(${PROJECT_NAME} ${SRC_LIST})

