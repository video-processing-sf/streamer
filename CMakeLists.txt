cmake_minimum_required(VERSION 3.10)
project(streamer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(streamer-bin
	src/main.cpp
	# source files
)

