cmake_minimum_required(VERSION 3.10)

PROJECT(hex_clock_app)

set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Ofast")

include_directories(
	${CMAKE_SOURCE_DIR}/inc
	${CMAKE_SOURCE_DIR}/inc/common
	${CMAKE_SOURCE_DIR}/inc/clock_loop
	${CMAKE_SOURCE_DIR}/inc/main_loop
	${CMAKE_SOURCE_DIR}/inc/display_loop
	${CMAKE_SOURCE_DIR}/common/include
	${CMAKE_SOURCE_DIR}/common/include/opencv/opencv2
	${CMAKE_SOURCE_DIR}/common/include/opencv/opencv2/core
	${CMAKE_SOURCE_DIR}/common/include/opencv/opencv2/highgui
	${CMAKE_SOURCE_DIR}/common/include/opencv/opencv2/imgproc
	${CMAKE_SOURCE_DIR}/common/include/opencv/opencv2/imgcodecs
)

set(LIBOPENCV_PATH ${CMAKE_SOURCE_DIR}/common/libs/opencv)
set(LIBOPENCV_LIB  ${LIBOPENCV_PATH}/libopencv_core.so
				   ${LIBOPENCV_PATH}/libopencv_highgui.so 
				   ${LIBOPENCV_PATH}/libopencv_imgcodecs.so 
				   ${LIBOPENCV_PATH}/libopencv_imgproc.so
				   ${LIBOPENCV_PATH}/libopencv_videoio.so)

file(GLOB_RECURSE SRC_FILES
	${CMAKE_SOURCE_DIR}/common/src/*.cc
	${CMAKE_SOURCE_DIR}/common/src/*.cpp
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cc
	${CMAKE_SOURCE_DIR}/src/*.cpp	
)

add_executable(${CMAKE_PROJECT_NAME} 
	 ${SRC_FILES}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
	${LIBOPENCV_LIB}
	pthread
    rt  
    dl 
	m
 )
 