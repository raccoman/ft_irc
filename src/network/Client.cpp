#include <iostream>
#include "network/Client.hpp"

Client::Client(int fd, const pollfds_iterator &pollfd, const std::string &hostname, int port)
		: _fd(fd), _pollfd(pollfd), _hostname(hostname), _port(port), _state(HANDSHAKE), _channel(nullptr) {
}

Client::~Client() {}

void Client::sendMessage(const std::string &message) const {
	std::string buffer = message + "\r\n";

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

void Client::join(Channel *channel) {

	channel->addClient(this);
	_channel = channel;

	channel->broadcast(RPL_JOIN(_nickname, channel->getName()));

	std::string admins;
	std::vector<std::string> nicknames = channel->getNicknames();
	for (std::vector<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); it++)
		admins.append(it.operator*() + " ");

	sendMessage(RPL_NAMREPLY(_nickname, channel->getName(), admins));
	sendMessage(RPL_ENDOFNAMES(_nickname, channel->getName()));

	char message[100];
	sprintf(message, "%s has joined channel %s.", _nickname.c_str(), channel->getName().c_str());
	ft_log(message);
}

void Client::leave() {

	if (!_channel) return;

	_channel->removeClient(this);

	char message[100];
	sprintf(message, "%s has left channel %s.", _nickname.c_str(), _channel->getName().c_str());
	ft_log(message);

	_channel = nullptr;
}
