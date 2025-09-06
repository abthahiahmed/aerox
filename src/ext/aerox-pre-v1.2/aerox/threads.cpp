#include "aerox.hpp"

atomic<bool> Aerox::isServerRunning = false;

atomic<bool> serverRunning{false};

void Aerox::runServer(){
	
	pid_t pid = fork();
	
	serverRunning = true;

	if (pid == 0){
		execl("./main", NULL);
		_exit(1);
	}else{
		while (serverRunning) {  };
		int status;
        pid_t result = waitpid(pid, &status, WNOHANG);
		
		cout<<"Server terminated"<<endl;
		kill(pid, SIGTERM); // Request graceful termination
		waitpid(pid, &status, 0);
		cout<<"Server starting..."<<endl;
		runServer();
	}
}
void Aerox::tailwindcss(){
	string tailwindcss = "npx @tailwindcss/cli -i ./styles/styles.css -o ./src/css/styles.css --watch";
	system(tailwindcss.c_str());
}

void Aerox::detectFilechanges(vector<string> files, func fn){
	
	int size = static_cast<int>(files.size());
	
	vector<int> mod_times(size, 0);
	vector<int> prev_mod_times(size, 0);

	struct stat result;
	while (true){
		
		for (unsigned i = 0; i < files.size(); i++){
			
			int s = stat(files[i].c_str(), &result);
			
			if(s == 0)
			{
				prev_mod_times[i] = mod_times[i];
				mod_times[i] = result.st_mtime;

				if (mod_times[i] == 0 || prev_mod_times[i] == 0) continue;
				
				if (mod_times[i] != prev_mod_times[i]){
					cout<<mod_times[i]<<" "<<prev_mod_times[i]<<endl;
					cout<<"File changes detected on "<<files[i]<<endl;
					
					fn(i);
					
					serverRunning = false;
				}
			}else{
				break;
			}
		}
	}
}