cmake_minimum_required(VERSION 3.20)
project(ft_irc)
set(CMAKE_CXX_STANDARD 98)

include_directories(include)
set(SOURCES
		src/Server.cpp src/Client.cpp include/Client.hpp)

add_executable(ft_irc src/main.cpp ${SOURCES})
