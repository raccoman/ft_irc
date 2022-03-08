#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command;

#include <string>
#include "network/Client.hpp"
#include "network/Server.hpp"

// ERROR REPLIES
#define ERR_NEEDMOREPARAMS(command) "461 " command " * :Not enough parameters"
#define ERR_ALREADYREGISTERED "462 * :You may not reregister"
#define ERR_PASSWDMISMATCH "464 * :Password incorrect"
#define ERR_NICKNAMEINUSE "433 * :Nickname is already in use"
#define ERR_NONICKNAMEGIVEN "431 * :Nickname not given"

class Command
{

protected:
    Server *_server;

public:
    Command(Server *server) : _server(server){};
    virtual ~Command(){};

    virtual void execute(Client *client, std::vector<std::string> arguments) = 0;
};

class UserCommand : public Command
{
public:
    UserCommand(Server *server);
    ~UserCommand();

    void execute(Client *client, std::vector<std::string> arguments);
};

class NickCommand : public Command
{
public:
    NickCommand(Server *server);
    ~NickCommand();

    void execute(Client *client, std::vector<std::string> arguments);
};

class PassCommand : public Command
{
public:
    PassCommand(Server *server);
    ~PassCommand();

    void execute(Client *client, std::vector<std::string> arguments);
};

#endif // COMMAND_HPP