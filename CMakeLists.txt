cmake_minimum_required(VERSION 3.20)
project(ft_irc)
set(CMAKE_CXX_STANDARD 98)

include_directories(include)
include_directories(include/network)
include_directories(include/commands)

set(SOURCES
		include/Utils.hpp
		src/network/Server.cpp
		src/network/Client.cpp
		src/network/Channel.cpp
		include/network/Channel.hpp
		src/commands/CommandHandler.cpp
		src/commands/impl/NickCommand.cpp
		src/commands/impl/PassCommand.cpp
		src/commands/impl/UserCommand.cpp
		src/commands/impl/JoinCommand.cpp
		src/commands/impl/QuitCommand.cpp
		)

add_executable(ft_irc src/main.cpp ${SOURCES})
