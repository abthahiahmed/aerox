#include "response.hpp"

Response::Response(TCPsocket client){
	this->response.append("HTTP/1.1 200 OK\n");
	this->response.append("Server: C++\n");
	this->client = client;
}


void Response::send(string content){
	this->response.append("Content-Type: text/html\n");
	this->response.append("Content-Length: " + to_string(content.length())+ "");
	this->response.append("\n\n");
	this->response.append(content);
	
	if (this->client){
		SDLNet_TCP_Send(this->client, response.c_str(), this->response.length());
	}
}

void Response::sendFile(string content, string contentType){
	this->response.append("Content-Type: " + contentType + "\n");
	this->response.append("Content-Length: " + to_string(content.length())+ "\n");
	this->response.append("Accept-Ranges: bytes");
	this->response.append("\n\n");
	this->response.append(content);
	
	if (this->client){
		SDLNet_TCP_Send(this->client, response.c_str(), this->response.length());
	}
}