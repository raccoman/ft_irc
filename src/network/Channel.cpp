//
// Created by Roberto Boldini on 3/9/22.
//

#include "../include/network/Channel.hpp"

Channel::Channel(const std::string &name, const std::string &password, Client *admin)
	: _name(name), _password(password), _admin(admin) {
	_clients.push_back(admin);
};

Channel::~Channel() {};

std::vector<Client *>::iterator Channel::getClient(Client *client) {
	for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		if ((*it) == client) {
			return it;
		}
	}
	return _clients.end();
}

void Channel::removeClient(Client *client) {
	client_iter it;
	if ((it = getClient(client)) != _clients.end()) {
		_clients.erase(it);
		ft_log(" Client kicked.");
//		TODO: reply to channel "[USERNAME] KICKED."
	}
	else {
		ft_log(" Client doesn't exist.");
	}
}

void Channel::sendMessage(const std::string& message, const std::string& sender) {
	for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		char msg[100];
		sprintf(msg, ":%s PRIVMSG #%s: %s.\n\r", sender.c_str(), _name.c_str(), message.c_str());
		(*it)->sendMessage(msg);
	}
}
