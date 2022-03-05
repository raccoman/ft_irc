#ifndef FT_IRC_LOGGER_HPP
#define FT_IRC_LOGGER_HPP

#include <iostream>
#include <string>
#include <time.h>

static void ft_log(const std::string &message)
{
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	std::string str(buffer);
	std::cout << "[" << str << "] " << message << std::endl;
};

#endif // FT_IRC_LOGGER_HPP