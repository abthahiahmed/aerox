#pragma once

#ifndef AEROX
#define AEROX

#include <iostream>
#include <filesystem>
#include <fstream>
#include <functional>
#include <string>
#include <regex>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <thread>
#include <atomic>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif

using namespace std;

using func = function<void(int index)>;

class Aerox{
	
private:
	// Structure for metadata
	struct MetaData { 
		string title;
		string description;
	};
	

	// Global variables for tracking
	vector<string> renderFunctions;
	vector<string> renderFunctionCalls;
	vector<string> renderRoutes;
	unordered_map<string, MetaData> metaData;
	vector<string> componentFunctions;
	vector<string> errors;
	vector<string> allFiles;
	vector<string> allParsedFiles;
	
	
	static atomic<bool> isServerRunning;
	bool tailwindcssEnabled;
	bool developmentMode;
	
	filesystem::path pagesDir;
	filesystem::path componentsDir;
	string targetBuildPath;
	
	// Functions
	string getFileContent(string path);
	string parseContent(string file, string code, bool isComponent);
	void generateParsedCode(string filename, string content);
	void generateParsedComponent(string filename, string content);
	void generatePages();
	void generateMetadata();
	void generateComponents();
	void generateRenders();
	void parseAndBuild();
	void singleParseAndBuild(string file);
	bool replace(std::string& str, const std::string& from, const std::string& to);
	string toRoute(string filename);
	
	// Threads functions
	static void runServer();
	static void tailwindcss();
	static void detectFilechanges(vector<string> files, func fn);

	
public:
	Aerox();
	void run();
	void disableTailwindcss();
	void enableDevelopment();
	
};


#endif