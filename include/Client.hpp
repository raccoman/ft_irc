#ifndef FT_IRC_CLIENT_HPP
#define FT_IRC_CLIENT_HPP

#include <vector>
#include <string>
#include <sys/poll.h>

class Client
{

	typedef std::vector<pollfd>::iterator pollfds_iterator;

private:
	int _fd;
	pollfds_iterator _pollfd;
	std::string _hostname;
	int _port;
	std::string _message;
	std::string _nick;
	std::string _fullName;


public:
	Client(int fd, pollfds_iterator pollfd, const std::string &hostname, int port);
	~Client();

	int getFD() { return _fd; };
	pollfds_iterator getPollFD() { return _pollfd; };
	std::string getHostname() { return _hostname; };
	int getPort() { return _port; };
};

#endif
