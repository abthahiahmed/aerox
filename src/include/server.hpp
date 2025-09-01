#pragma once
#include <iostream>
#include <functional>
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "request.hpp"
#include "response.hpp"
#include "render.hpp"

using namespace std;

class Server{
	
private:
	TCPsocket server;
	TCPsocket client;
	
	string staticDir;
	
	using func = function<void(Request, Response)>;
	unordered_map<string, func> getRequests;
	unordered_map<string, func> postRequests;
	
	unordered_map<string, string> mediaTypeByExt;
	
	vector<string> routes;
public:
	Server(int port);
	~Server();
	void loadMediaTypes();
	void setStaticDir(string dir);
	bool handleStaticFiles(Response res, string filename);
	void get(string path, func fn);
	void post(string path, func fn);
	void listen();
	
};
