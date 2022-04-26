cmake_minimum_required(VERSION 3.20)
project(ft_irc)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCES src/IrcBot.cpp)

add_executable(ft_irc src/main.cpp ${SOURCES})
