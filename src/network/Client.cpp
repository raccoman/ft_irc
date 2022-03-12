#include <iostream>
#include "network/Client.hpp"

Client::Client(int fd, const pollfds_iterator &pollfd, const std::string &hostname, int port)
		: _fd(fd), _pollfd(pollfd), _hostname(hostname), _port(port), _state(HANDSHAKE), _channel(nullptr) {
}

Client::~Client() {}

void Client::sendMessage(const std::string &message) const {
	std::string buffer = message + "\n\r";

	if (send(_fd, buffer.c_str(), buffer.length(), 0) < 0)
		throw std::runtime_error("Error while sending message to client.");
}

void Client::welcome() {
	if (_state != LOGIN || _username.empty() || _realname.empty() || _nickname.empty())
		return;
	_state = PLAY;

	sendMessage(RPL_WELCOME(_nickname));

	char message[100];
	sprintf(message, "%s:%d is now known as %s.", _hostname.c_str(), _port, _nickname.c_str());
	ft_log(message);
}

