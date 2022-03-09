#ifndef FT_IRC_CLIENT_HPP
#define FT_IRC_CLIENT_HPP

class Client;

#include <vector>
#include <string>
#include <sys/poll.h>
#include <sys/socket.h>
#include "../Utils.hpp"

class Client
{

	typedef std::vector<pollfd>::iterator pollfds_iterator;

private:
	int _fd;
	pollfds_iterator _pollfd;
	std::string _hostname;
	int _port;

	std::string _nickname;
	std::string _username;
	std::string _realname;

	bool _registered;
	bool _entered; // Only checks for pass

public:
	Client(int fd, const pollfds_iterator &pollfd, const std::string &hostname, int port);
	~Client();

	int getFD() const { return _fd; };
	pollfds_iterator getPollFD() const { return _pollfd; };
	std::string getHostname() const { return _hostname; };
	int getPort() const { return _port; };
	bool isRegistered() const { return _registered; };
	std::string getNickname() const { return _nickname; };
	std::string getUsername() const { return _username; };
	std::string getRealName() const { return _realname; };

	void setNickname(const std::string &nickname) { _nickname = nickname; };
	void setUsername(const std::string &username) { _username = username; };
	void setRealName(const std::string &realname) { _realname = realname; };
	void setRegistered(const bool value) { _registered = value; };
	void setEntered(const bool value) { _entered = value; };

	void checkRegistered();
	void sendMessage(const std::string &message);
};

#endif
