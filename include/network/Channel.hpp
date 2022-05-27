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
	Client					*_admin;
	std::vector<Client *>	_clients;

	/** Modes */
	std::string				_k;
	size_t					_l;
	bool					_n;

public:
	Channel(const std::string &name, const std::string &password, Client *admin);
	~Channel();

	Client* getAdmin() { return _admin; };
	std::string getName() const { return _name; };

	std::string getPassword() const { return _k; };
	void		setPassword(std::string k) { this->_k = k; };
	size_t		getMaxClients() const { return _l; };
	void		setMaxClients(size_t l) { this->_l = l; };
	bool		isNoExt() const { return _n; };
	void		setNoExt(bool n) { this->_n = n; };


	size_t						getNumClients() const { return _clients.size(); };
	std::vector<std::string>	getNicknames();

	void broadcast(std::string const &message);
	void broadcast(const std::string &message, Client *exclude);
	void removeClient(Client *client);
	void addClient(Client *client) { _clients.push_back(client); };
	void kick(Client *client, Client *target, const std::string &reason);

};

#endif //FT_IRC_CHANNEL_HPP
