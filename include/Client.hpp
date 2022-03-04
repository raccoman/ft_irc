#ifndef FT_IRC_CLIENT_HPP
#define FT_IRC_CLIENT_HPP

#include <string>

class Client {

private:
	int _fd;
	std::string _hostname;
	int _port;
	std::string _message;

public:
	Client(int fd, const std::string &hostname, int port);
	~Client();

	int			getFD() { return _fd; };
	std::string	getHostname() { return _hostname; };
	int			getPort() { return _port; };

};

#endif
