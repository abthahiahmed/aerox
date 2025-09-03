#include "document.hpp"

string Head(){
	string head = "<head>"
            "<meta charset=\"UTF-8\">"
            "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
            "<title>" + __title__ + "</title>"
            "<meta name=\"description\" content=\"" + __description__ + "\"/>"
            "<link rel=\"stylesheet\" href=\"/styles/css\"/>"
			"</head>";
	
	return head;
	
}
string AScript(){
	string script = "<script src=\"/_aerox/js/csr.js\"></script>";
	
	return script;
}