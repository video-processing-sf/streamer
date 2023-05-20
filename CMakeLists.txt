cmake_minimum_required(VERSION 3.10)
project(streamer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(streamer-bin
	src/main.cpp
	src/video_streamer.cpp
	src/video_streamer.h
	src/shared_memory.cpp
	src/shared_memory.h
	src/csi_camera.cpp
	src/csi_camera.h
	src/frame.cpp
	src/frame.h
	src/types.h
)

