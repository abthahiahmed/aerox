#include "request.hpp"


string Request::decodeData(string data){
	string ret;
    char ch;
    unsigned i, ii, len = data.length();

    for (i = 0; i < len; i++) {
        if (data[i] != '%') {
            if (data[i] == '+')
                ret += ' ';
            else
                ret += data[i];
        }
        else {
            sscanf(data.substr(i + 1, 2).c_str(), "%x", &ii);
            ch = static_cast<char>(ii);
            ret += ch;
            i = i + 2;
        }
    }
    return ret;
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


vector<string> splitString(string text, char delimiter){
	vector<string> parts;
	istringstream stream(text);
	string part;
	while(getline(stream, part, delimiter)){
		parts.emplace_back(part);
	}
	return parts;
}

void Request::getPathAndParams(string& path, unordered_map<string, string>& params, vector<string> routes){
	vector<string> urlParts = splitString(path, '/');
	
	vector<vector<string>> routesParts = {};
	vector<string> filteredRoutes = {};
	
	// Route part filter by matching the size of parts
	for (unsigned i = 0; i < routes.size(); i++){
		
		vector<string> routeParts = splitString(routes[i], '/');
		
		if (routeParts.size() == urlParts.size()){
			routesParts.emplace_back(routeParts);
			filteredRoutes.emplace_back(routes[i]);
		}
	}
	
	string _path = "";
	
	for (unsigned i = 0; i < routesParts.size(); i++){
		bool prevMatch = false;
		for (unsigned j = 1; j < routesParts[i].size(); j++){
			
			if (routesParts[i][j] == urlParts[j]){
				prevMatch = true;
			}
			else if (prevMatch && routesParts[i][j][0] == '['){
				string key = routesParts[i][j].substr(1, routesParts[i][j].length() - 2);
				params[key] = urlParts[j];
			}
			else{
				prevMatch = false;
				break;
			}
		}
		if (prevMatch) _path = filteredRoutes[i];
	}
	
	if (_path != "") path = _path;
	
	return;
}

Request::Request(const char *request, vector<string>& routes){
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
	
	this->getPathAndParams(path, this->params, routes);
	
	// Parse Body
	this->body = parseBody(line);
	this->method = tokens[0];	
	this->path = path;
	this->protocol = tokens[2];
	this->host = tokens[4];
	this->userAgent = tokens[6];
	
}

