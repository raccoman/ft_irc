//
// Created by Roberto Boldini on 3/9/22.
//
#ifndef FT_IRC_CHANNEL_HPP
# define FT_IRC_CHANNEL_HPP

class Channel;

# include "Server.hpp"
# include "Client.hpp"

class Channel {

	typedef std::vector<Client *>::iterator clients_iterator;

private:
	std::string				_name;
	std::string				_password;
	Client *				_admin;
	std::vector<Client *>	_chanops;
	std::vector<Client *>	_clients;


public:
	Channel(const std::string &name, const std::string &password, Client *admin);
	~Channel();

	Client* getAdmin() { return _admin; };
	std::string getName() const { return _name; };
	std::string getPassword() const { return _password; };
	std::vector<Client *> getClients() const { return _clients; };
	std::vector<Client *> getChanops() const { return _chanops; };
	std::vector<std::string> getNicknames();

	void broadcast(std::string const &message);
	//void sendMessage(const std::string& message, const std::string& sender);
	void removeClient(Client *client);
	void addClient(Client *client) { _clients.push_back(client); };

};

#endif //FT_IRC_CHANNEL_HPP
