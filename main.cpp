#include <iostream>
#include "./src/include/server.hpp"

using namespace std;

int main(int argc, char **argv)
{
	
	Server server = Server(8080);

	server.post("/contact", [](Request req, Response res){
		string message = "Your data is saved. Email : " + req.body["email"] + ", Name : " + req.body["name"];
		res.send(message);
	});
	
	cout<<"C++ web server started..."<<endl;
	server.listen();
	
	return 0;
}
