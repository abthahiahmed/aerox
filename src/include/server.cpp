#include "server.hpp"


Server::Server(int port){
	SDLNet_Init();
	IPaddress ip;
	SDLNet_ResolveHost(&ip, NULL, port);
	this->server = SDLNet_TCP_Open(&ip);
	this->loadMediaTypes();
	this->setBuiltinStaticFilesDirectory();
	initRenders();
	
	for (auto key: pages){
		this->routes.emplace_back(key.first);
	}
	this->staticDir = "./public";

}

Server::~Server(){
	SDLNet_TCP_Close(this->server);
	SDLNet_Quit();
}



void Server::setStaticDir(string dir){
	this->staticDir = dir;
}

bool Server::handleStaticFiles(Response res, string filename){
	
	string pathToFile = this->staticDir + filename;
	
	if (systemFiles[filename] != ""){
		pathToFile = systemFiles[filename];
	}
	
	ifstream file(pathToFile, ios::binary);
	
	if (!file.is_open()) return false;
	
	filesystem::path filePath = filename;
	
	string extension = filePath.extension().string();
	
	string line;
	string content = "";
	
	while (getline(file, line)){
		content += line + "\n";
	}
	if (content != "") {
		content.pop_back();
	}
	
	res.sendFile(content, this->mediaTypeByExt[extension]);
	
	return true;
}

void Server::listen(){
	char request[1024];
	memset(request, '\0', sizeof(request));
	while(true){
		
		this->client = SDLNet_TCP_Accept(this->server);
		
		if (this->client){

			SDLNet_TCP_Recv(client, request, 1024);
			

			Request req = Request(request, this->routes);
			Response res = Response(this->client);
			
			if (req.method == "GET"){
				// Filebased Routing
				if (pages[req.path]){
					pages[req.path](req, res);
				}
				// API Routing
				else if (this->getRequests[req.path]){
					this->getRequests[req.path](req, res);
				}
				// Public Assets
				else if (!handleStaticFiles(res, req.path)){
					res.send("Not Found!");
				}
			}
			else if (req.method == "POST"){
				if (this->postRequests[req.path]){
					this->postRequests[req.path](req, res);
				}else{
					res.send("Not Found!");
				}
			}
			
			SDLNet_TCP_Close(this->client);
			
			memset(request, '\0', sizeof(request));
		}
		
	}
}

void Server::get(string path, func fn){
	this->getRequests[path] = fn;
}
void Server::post(string path, func fn){
	this->postRequests[path] = fn;
}

void Server::loadMediaTypes(){
	
	this->mediaTypeByExt = {
		{".aac", "audio/aac"},
		{".abw", "application/x-abiword"},
		{".apng", "image/apng"},
		{".arc", "application/x-freearc"},
		{".avif", "image/avif"},
		{".avi", "video/x-msvideo"},
		{".azw", "application/vnd.amazon.ebook"},
		{".bin", "application/octet-stream"},
		{".bmp", "image/bmp"},
		{".bz", "application/x-bzip"},
		{".bz2", "application/x-bzip2"},
		{".cda", "application/x-cdf"},
		{".csh", "application/x-csh"},
		{".css", "text/css"},
		{".csv", "text/csv"},
		{".doc", "application/msword"},
		{".docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
		{".eot", "application/vnd.ms-fontobject"},
		{".epub", "application/epub+zip"},
		{".gz", "application/gzip"},
		{".gif", "image/gif"},
		{".htm", "text/html"},
		{".html", "text/html"},
		{".ico", "image/vnd.microsoft.icon"},
		{".ics", "text/calendar"},
		{".jar", "application/java-archive"},
		{".jpeg", "image/jpeg"},
		{".jpg", "image/jpeg"},
		{".js", "text/javascript"},
		{".json", "application/json"},
		{".jsonld", "application/ld+json"},
		{".md", "text/markdown"},
		{".mid", "audio/midi"},
		{".midi", "audio/x-midi"},
		{".mjs", "text/javascript"},
		{".mp3", "audio/mpeg"},
		{".mp4", "video/mp4"},
		{".mpeg", "video/mpeg"},
		{".mpkg", "application/vnd.apple.installer+xml"},
		{".odp", "application/vnd.oasis.opendocument.presentation"},
		{".ods", "application/vnd.oasis.opendocument.spreadsheet"},
		{".odt", "application/vnd.oasis.opendocument.text"},
		{".oga", "audio/ogg"},
		{".ogv", "video/ogg"},
		{".ogx", "application/ogg"},
		{".opus", "audio/ogg"},
		{".otf", "font/otf"},
		{".png", "image/png"},
		{".pdf", "application/pdf"},
		{".php", "application/x-httpd-php"},
		{".ppt", "application/vnd.ms-powerpoint"},
		{".pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"},
		{".rar", "application/vnd.rar"},
		{".rtf", "application/rtf"},
		{".sh", "application/x-sh"},
		{".svg", "image/svg+xml"},
		{".tar", "application/x-tar"},
		{".tif", "image/tiff"},
		{".tiff", "image/tiff"},
		{".ts", "video/mp2t"},
		{".ttf", "font/ttf"},
		{".txt", "text/plain"},
		{".vsd", "application/vnd.visio"},
		{".wav", "audio/wav"},
		{".weba", "audio/webm"},
		{".webm", "video/webm"},
		{".webmanifest", "application/manifest+json"},
		{".webp", "image/webp"},
		{".woff", "font/woff"},
		{".woff2", "font/woff2"},
		{".xhtml", "application/xhtml+xml"},
		{".xls", "application/vnd.ms-excel"},
		{".xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
		{".xml", "application/xml"},
		{".xul", "application/vnd.mozilla.xul+xml"},
		{".zip", "application/zip"},
		{".3gp", "video/3gpp"},
		{".3g2", "video/3gpp2"},
		{".7z", "application/x-7z-compressed"}
	};
	
}
void Server::setBuiltinStaticFilesDirectory(){ // Internal non-c++ files (Javascript, CSS etc)
	systemFiles["/_aerox/js/csr.js"] = "./src/js/csr.js";
}