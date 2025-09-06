#include "./aerox.hpp"

int main(int argc, char **argv){
	
	Aerox aerox = Aerox();
	
	aerox.enableDevelopment();
	aerox.run();
	
	
	return 0;
}