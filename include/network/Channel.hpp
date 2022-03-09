//
// Created by Roberto Boldini on 3/9/22.
//
#ifndef FT_IRC_CHANNEL_HPP
#define FT_IRC_CHANNEL_HPP

class Channel;

#include "Server.hpp"
#include "Client.hpp"

class Channel {
private:
	std::string				_name;
	Client *				_admin;
	std::string				_password;
	std::vector<Client *>	_clients;


public:
	Channel(const std::string &name, const std::string &password, Client *admin);
	~Channel();

	
	void addClient(Client *newClient) { _clients.push_back(newClient); };
	void removeClient(Client *client) { _clients.erase(client); };

};

#endif //FT_IRC_CHANNEL_HPP
