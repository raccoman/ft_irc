#include <iostream>
#include "network/Client.hpp"

Client::Client(int fd, const pollfds_iterator &pollfd, const std::string &hostname, int port)
	: _fd(fd), _pollfd(pollfd), _hostname(hostname), _port(port), _registered(false) {
}

Client::~Client() {}

void Client::sendMessage(const std::string &message)
{
	std::string buffer = message + "\n\r";

	if (send(_fd, buffer.c_str(), buffer.length(), 0) < 0)
		throw std::runtime_error("Error while sending message to client.");
}

void Client::checkRegistered() {
	if(_entered && !(_nickname.empty()) && !(_username.empty())){
		sendMessage(RPL_WELCOME(_nickname));
		setRegistered(true);
	}
}