#ifndef FT_IRC_IRCBOT_HPP
#define FT_IRC_IRCBOT_HPP

#include <iostream>
#include <string>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

class IrcBot {
public:
	IrcBot(const std::string &host, const std::string &port, const std::string &password);
	~IrcBot();

	void start();
	void onMessageReceived(const std::string &message);

private:
	int			_running;
	int			_sock;
	std::string	_host;
	std::string	_port;
	std::string	_password;

	int newSocket();
	void authenticate(const std::string &nick);
	void flush(const std::string &message);
	static void receiver(IrcBot *instance);
};

#endif
