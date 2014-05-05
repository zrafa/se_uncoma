include_directories(${CMAKE_SOURCE_DIR}/headers)
LINK_LIBRARIES(myro-cpp)

add_executable(myro_graphwin_test graphwin_test.cpp)
add_executable(myro_polygon_test polygon_test.cpp)
add_executable(myro_circles circles.cpp)
add_executable(myro_joystick robot_joystick.cpp)
add_executable(myro_senses robot_senses.cpp)
add_executable(myro_cascading_pictures cascading_pictures.cpp)

INSTALL(TARGETS myro_senses myro_joystick RUNTIME DESTINATION bin)

INSTALL(FILES Makefile circles.cpp robot_joystick.cpp robot_senses.cpp cascading_pictures.cpp DESTINATION "share/doc/myro-cpp-${PKG_VERSION}/examples/graphics" )
