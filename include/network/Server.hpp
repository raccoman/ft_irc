#ifndef FT_IRC_SERVER_HPP
# define FT_IRC_SERVER_HPP

class Server;

#include <algorithm>
#include <sys/poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include <poll.h>

#include "commands/CommandHandler.hpp"
#include "Client.hpp"
#include "Channel.hpp"

#define MAX_CONNECTIONS 1000
#define MSG_DELIMITER "\n\r"

class Server
{

	typedef std::vector<pollfd>::iterator pollfds_iterator;

	int							_running;
	int							_sock;
	const std::string			_host;
	const std::string			_port;
	const std::string			_password;
	std::vector<pollfd>			_pollfds;
	std::map<int, Client *>		_clients;
	std::map<int, std::string>	_messages;
	std::vector<Channel *>		_channels;
	CommandHandler*				_commandHandler;

public:
	Server(const std::string &port, const std::string &password);
	~Server();

	void start();

	std::string getPassword() const { return _password; };
	Client *getClient(const std::string &nickname);
	Channel* getChannel(const std::string &name);
	void addChannel(const std::string &name, const std::string &password, Client *client);
	void removeClient(Client *client);
	void removeChannel(Channel *channel);


	void printChannels();// DEBUG
	std::vector<Channel *>::iterator getChannelIterator(Channel *channel);

	int newSocket();
	void onClientDisconnect(int fd);
	void onClientConnect();
	void onClientMessage(int fd);
	std::string readMessage(int fd);

};

#endif
