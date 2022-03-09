//
// Created by Roberto Boldini on 3/9/22.
//

#include "Channel.hpp"

Channel::Channel(const std::string &name, const std::string &password, Client *admin)
	: _name(name), _password(password), _admin(admin) {
	_clients.push_back(admin);
};

Channel::~Channel() {};