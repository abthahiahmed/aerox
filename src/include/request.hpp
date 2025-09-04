#pragma once
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;


class Request{
	
private:
	unordered_map<string, string> parseQuery(string query);
	unordered_map<string, string> parseBody(string body);
	string decodeData(string data);
	string url;
	
	void getPathAndParams(string& path, unordered_map<string, string>& params, vector<string> routes);
public:
	string protocol;
	string path;
	string method;
	string host;
	string userAgent;
	unordered_map<string, string> query;
	unordered_map<string, string> body;
	unordered_map<string, string> params;

	string getDynamicRoute(vector<string>& routes);
	
	Request(const char *request, vector<string>& routes);
	
	
	
};
#endif