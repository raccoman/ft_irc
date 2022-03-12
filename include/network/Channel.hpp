//
// Created by Roberto Boldini on 3/9/22.
//
#ifndef FT_IRC_CHANNEL_HPP
#define FT_IRC_CHANNEL_HPP

class Channel;

# include "Server.hpp"
# include "Client.hpp"

class Channel {

	typedef std::vector<Client *>::iterator client_iter;
private:
	std::string				_name;
	std::string				_password;
	Client *				_admin;
	std::vector<Client *>	_clients;


public:
	Channel(const std::string &name, const std::string &password, Client *admin);
	~Channel();

	Client* getAdmin() { return _admin; };
	std::string getName() const { return _name; };
	bool checkEmptyClients() { return _clients.empty(); };
	std::string getPassword() const { return _password; };
	std::vector<Client *>::iterator getClient(Client *client);

	void removeClient(Client *client);
	void addClient(Client *newClient) { _clients.push_back(newClient); };

};

#endif //FT_IRC_CHANNEL_HPP
