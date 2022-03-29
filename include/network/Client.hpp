#ifndef FT_IRC_CLIENT_HPP
# define FT_IRC_CLIENT_HPP

enum ClientState {
	HANDSHAKE,
	LOGIN,
	PLAY,
	DISCONNECTED
};

class Client;

#include <vector>
#include <string>
#include <sys/poll.h>
#include <sys/socket.h>
#include "utils.h"
#include "Channel.hpp"

class Client {

	typedef std::vector<pollfd>::iterator pollfds_iterator;

private:
	int _fd;
	pollfds_iterator _pollfd;
	std::string _hostname;
	int _port;

	std::string _nickname;
	std::string _username;
	std::string _realname;

	ClientState _state;

	Channel *_channel;

public:
	Client(int fd, const pollfds_iterator &pollfd, const std::string &hostname, int port);

	~Client();

	int getFD() const { return _fd; };

	pollfds_iterator getPollFD() const { return _pollfd; };

	std::string getHostname() const { return _hostname; };

	int getPort() const { return _port; };

	bool isRegistered() const { return _state == ::PLAY; };

	std::string getNickname() const { return _nickname; };

	std::string getUsername() const { return _username; };

	std::string getRealName() const { return _realname; };

	Channel *getChannel() const { return _channel; };

	void setNickname(const std::string &nickname) { _nickname = nickname; };

	void setUsername(const std::string &username) { _username = username; };

	void setRealName(const std::string &realname) { _realname = realname; };

	void setState(ClientState state) { _state = state; };

	void sendMessage(const std::string &message) const;

	void welcome();

	void join(Channel *channel);

	void leave();

	void kick(std::string op, Channel *channel);
};

#endif
