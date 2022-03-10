#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP

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
#include "logger.hpp"

#define MAX_CONNECTIONS 1000
#define MSG_DELIMITER "\n\r"

class Server
{

	typedef std::vector<pollfd>::iterator pollfds_iterator;

	int _sock;
	const std::string		_host;
	const std::string		_port;
	const std::string		_password;
	std::vector<pollfd>		_pollfds;
	std::map<int, Client *>	_clients;
	std::vector<Channel *>	_channels;
	CommandHandler*			_commandHandler;

public:
	Server(const std::string &port, const std::string &password);
	~Server();

	void start();

	std::string getPassword() const { return _password; };
	Client *getClient(const std::string &nickname);
	Channel* getChannel(const std::string &name);
	void addChannel(const std::string &name, const std::string &password) {};

private:
	int newSocket(int nonblocking = 0);
	void onClientConnect();
	void onClientDisconnect(int fd);
	void onClientMessage(int fd);
	std::string readMessage(int fd);
};

#endif
