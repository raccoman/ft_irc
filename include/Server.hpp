#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include <poll.h>
#include <time.h>

#include "Client.hpp"

#define HANDSHAKE_MESSAGE "PASS NICK USER\n\r"

#define MAX_CONNECTIONS 1000

class Server {

	typedef std::vector<pollfd>::iterator	pollfds_iterator;

	int							_sock;
	const std::string			_host;
	const std::string			_port;
	const std::string			_password;
	std::vector<pollfd>			_pollfds;
	std::map<int, Client*>		_clients;

public:
	Server(const std::string &port, const std::string &password);
	~Server();

	void	start();

private:
	void		ft_log(const std::string &message);
	int			newSocket(int nonblocking = 0);
	Client		*acceptClient();
	std::string	readMessage(int fd);

};


#endif //SERVER_HPP
