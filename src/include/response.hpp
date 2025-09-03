#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <SDL2/SDL_net.h>

using namespace std;


class Response{
	
private:
	string response;
	TCPsocket client;
	
public:
	Response(TCPsocket client);
	void send(string content);
	void sendFile(string content, string contentType);
	void sendJSON(string);
	
	
};

#endif