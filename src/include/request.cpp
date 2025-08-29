#include "request.hpp"


string decodeData(string data){
	unsigned i = 0;
	
	while (i < data.length()){
		if (data[i] == '+'){
			data[i] = ' ';
		}
		i++;
	}
	return data;
}

unordered_map<string, string> Request::parseQuery(string query){
	unordered_map<string, string> result;
	
	vector<string> tokens;
	istringstream pss(query);
    string pair;
	string data;
	
	while(getline(pss, pair, '&')){
		string key;
		string value;
		istringstream dss(pair);
		getline(dss, key, '=');
		getline(dss, value, '=');
		result[key] = value;
//		cout<<"Query : "<<key<<" = "<<value<<endl;
	}
	
	return result;
}

unordered_map<string, string> Request::parseBody(string body){
	unordered_map<string, string> result;
	
	vector<string> tokens;
	istringstream pss(body);
    string pair;
	string data;
	
	while(getline(pss, pair, '&')){
		string key;
		string value;
		istringstream dss(pair);
		getline(dss, key, '=');
		getline(dss, value, '=');
		result[key] = decodeData(value);
//		cout<<"Body : "<<key<<" = "<<decodeData(value)<<endl;
	}
	
	return result;
}

Request::Request(const char *request){
	vector<string> tokens;
	string data = request;
	
    istringstream lss(data);
    string line;
	string token;
	
	while (getline(lss, line, '\n')) {
		
		istringstream tss(line);
		
		while(getline(tss, token, ' ')){
			tokens.push_back(token);
		}
	}
//	cout<<line<<endl;
	
//	cout<<data<<endl;
	string url = tokens[1];
	
	// Parse path
	string path = "";
	unsigned i = 0;
	while(url[i] != '?' && i < url.length()){
		path += url[i];
		i++;
	}
	
	// Parse Query Parameters
	url.replace(0, path.length() + 1, "");
	this->query = parseQuery(url);
	
	// Parse Body
	this->body = parseBody(line);
	
	
	
	
	this->method = tokens[0];	
	this->path = path;
	this->protocol = tokens[2];
	this->host = tokens[4];
	this->userAgent = tokens[6];
	
}

