#include <iostream>
#include "./src/include/server.hpp"

using namespace std;

int main(int argc, char **argv)
{
	
	Server server = Server(8080);
	
	server.setStaticDir("./public");
	
	server.get("/services", [](Request req, Response res){
		res.send("This is service page");
	});
	
	server.post("/form-action", [](Request req, Response res){
		res.send("This is service page");
	});
	
	cout<<"C++ web server started..."<<endl;
	server.listen();
	
	return 0;
}
