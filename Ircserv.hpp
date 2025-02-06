/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:43:49 by bde-souz          #+#    #+#             */
/*   Updated: 2025/02/06 15:55:04 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <map>
#include <vector>
#include <poll.h>
#include <sstream>


// COLORS //
#define blue "\033[34m"
#define red "\033[31m"
#define green "\033[32m"
#define yellow "\033[33m"
#define magenta "\033[35m"
#define cyan "\033[36m"
#define reset "\033[0m"


struct Client
{
	int			_fd;
	std::string _nickName;
	std::string _userName;
	std::string _realName;
};


class Ircserv 
{
private:
	// nome do canal - FDs dos usuarios
	std::map<std::string, std::vector<Client> > _channels;
	std::map<int, Client> _clientsMap;



	std::string		_password = "colhapos";
	unsigned int	_port;



	int				_clientFd;
	int				_serverFd;

	bool _checkStartPass(const std::string& pass);
	bool _checkStartPort(const unsigned int port);



public:
	void createServer(const std::string& pass, unsigned int port);
	void acceptClients();

	//Lida com as mensagens
	void bufferReader(int clientFd, char *buffer);


	//Commands
	void commandJoin(const std::string &channel);
	void commandNick(int clientFd, const std::string &str);
	void commandUser(std::istringstream &lineStream);
	void commandPrivMSG(std::istringstream &lineStream);

	//Help Functions
	bool checkIfClientInChannel(std::map<std::string, std::vector<Client> > channelMap, \
		std::string channel, int clientFd);
	bool checkIfClientInServer(int clientFd);
	bool checkIfClientInServerByNick(std::string clientNick);

	bool checkIfChannelExist(std::string channel);
	Client returnClientStruct(int clientFd);
	void makeUserList(std::string channel);
	int  returnClientFd(std::string clientNick);



	void broadcastMessageToChannel(const std::string& message, std::string channel);
	void broadcastMessageToChannelExceptSender(const std::string& message, std::string channel, int senderFd);
	void broadcastMessage(const std::string& message, int sender_fd);
	void broadcastMessagePrivate(const std::string &message, const std::string &target);


	//Debug
	void debugShowChannelsInfo();
	void debugShowLastClient(void);
	void debugShowAllClients(void);


	//Visual Functions
	void visualLoadingServer(void);

	
} ;
