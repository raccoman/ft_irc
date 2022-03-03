#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_CONNECTIONS 1000

class Server {

	int					_sock;
	const std::string	_host;
	const std::string	_port;
	const std::string	_password;

public:
	Server(const std::string &port, const std::string &password);
	~Server();

	void	start();

private:
	int		newSocket();

};


#endif //SERVER_HPP
