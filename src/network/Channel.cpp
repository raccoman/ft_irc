//
// Created by Roberto Boldini on 3/9/22.
//

#include "network/Channel.hpp"

Channel::Channel(const std::string &name, const std::string &password, Client *admin)
		: _name(name), _admin(admin), _k(password), _l(0), _n(false) {
}

Channel::~Channel() {}

std::vector<std::string> Channel::getNicknames() {
	std::vector<std::string> nicknames;

	for (clients_iterator it = _clients.begin(); it != _clients.end(); it++) {
		Client *client = it.operator*();
		nicknames.push_back((_admin == client ? "@" : "") + (*it)->getNickname());
	}

	return nicknames;
}

void Channel::broadcast(const std::string &message) {
	for (clients_iterator it = _clients.begin(); it != _clients.end(); it++)
		(*it)->write(message);
}

void Channel::broadcast(const std::string &message, Client *exclude) {
	for (clients_iterator it = _clients.begin(); it != _clients.end(); it++) {

		if (*it == exclude)
			continue;

		(*it)->write(message);
	}
}

void Channel::removeClient(Client *client) {

	_clients.erase(std::remove(_clients.begin(), _clients.end(), client), _clients.end());
	client->setChannel(nullptr);

	if (_clients.empty()) {
		//TODO: free Channel* and remove from _channels in Server
		return;
	}

	if (_admin == client) {
		_admin = _clients.begin().operator*();

		char message[100];
		sprintf(message, "%s is now admin of channel %s.", _admin->getNickname().c_str(), _name.c_str());
		ft_log(message);
	}
}

void Channel::kick(Client *client, Client *target, const std::string &reason) {

	broadcast(RPL_KICK(client->getPrefix(), _name, target->getNickname(), reason));
	removeClient(target);

	char message[100];
	sprintf(message, "%s kicked %s from channel %s.", client->getNickname().c_str(), target->getNickname().c_str(),
			_name.c_str());
	ft_log(message);
}
