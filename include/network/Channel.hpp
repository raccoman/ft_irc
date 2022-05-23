//
// Created by Roberto Boldini on 3/9/22.
//
#ifndef FT_IRC_CHANNEL_HPP
# define FT_IRC_CHANNEL_HPP

class Channel;

# include "Server.hpp"
# include "Client.hpp"
# include "utils.hpp"

class Channel {

	typedef std::vector<Client *>::iterator clients_iterator;

private:
	std::string				_name;
	std::string				_password;
	Client					*_admin;
	std::vector<Client *>	_clients;
	size_t					_max_clients;

public:
	Channel(const std::string &name, const std::string &password, Client *admin);
	~Channel();

	Client* getAdmin() { return _admin; };
	std::string getName() const { return _name; };
	size_t		getMaxClients() const { return _max_clients; };
	void		setMaxClients(size_t max_clients) { this->_max_clients = max_clients; };
	size_t		getNumClients() const { return _clients.size(); }; // size of vector is exact number of connected clients?
	std::string getPassword() const { return _password; };
	void		setPassword(std::string password) { this->_password = password; };
	std::vector<std::string> getNicknames();

	void broadcast(std::string const &message);
	void broadcast(const std::string &message, Client *exclude);
	void removeClient(Client *client);
	void addClient(Client *client) { _clients.push_back(client); };
	void kick(Client *client, Client *target, const std::string &reason);

};

#endif //FT_IRC_CHANNEL_HPP
