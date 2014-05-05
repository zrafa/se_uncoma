include_directories(${CMAKE_SOURCE_DIR}/headers)
LINK_LIBRARIES(myro-cpp)

add_executable(myro_test_motor test_motor.cpp)
add_executable(myro_test_camera test_camera.cpp)
add_executable(myro_test_camera_fourwindow test_camera_fourwindow.cpp)
add_executable(myro_test_camera_nonblocking test_camera_nonblocking.cpp)
add_executable(myro_test_blob test_blob.cpp)
add_executable(myro_video_stream video_stream.cpp)
add_executable(askQuestion askQuestion.cpp)
add_executable(myro_test_ir test_ir.cpp)
add_executable(myro_take_snapshot take_snapshot.cpp)
add_executable(myro_test_stall test_stall.cpp)

INSTALL(TARGETS myro_take_snapshot myro_test_ir myro_test_motor myro_test_camera myro_test_blob myro_video_stream RUNTIME DESTINATION bin)
#INSTALL(TARGETS myro_test_motor myro_test_camera myro_video_stream RUNTIME DESTINATION bin)

INSTALL( FILES README Makefile test_motor.cpp test_camera.cpp test_camera_fourwindow.cpp test_camera_nonblocking.cpp test_blob.cpp video_stream.cpp DESTINATION "share/doc/myro-cpp-${PKG_VERSION}/examples" )

ADD_SUBDIRECTORY(graphics)
