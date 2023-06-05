cmake_minimum_required(VERSION 3.10)
project(streamer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED
	gstreamer-1.0
	gstreamer-app-1.0
)

find_package(OpenCV REQUIRED)


add_executable(streamer-bin
	src/main.cpp
	src/csi_camera.cpp
	src/shared_memory.cpp
	src/video_streamer.cpp
)

target_include_directories(streamer-bin PRIVATE
	${GSTREAMER_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/
)

target_link_libraries(streamer-bin
	${GSTREAMER_LIBRARIES}
	pthread
	rt
)

