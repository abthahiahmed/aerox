#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <ctime>

using namespace std;

vector<string> renderFunctions;
vector<string> renderFunctionCalls;
vector<string> renderRoutes;

vector<string> componentFunctions;

string getFileContent(string path){
	ifstream file(path);
	
	if (!file.is_open()) return "";
	
	string content = "";
	string line;
	while (getline(file, line)){
		content += line + "\n";
	}
	
	file.close();
	return content;
}

string parseContent(string code, bool isComponent = false){

	string newCode = "";
	
	
	for (int i = 0; i < code.length(); i++){
		
		if (code[i] == '/' && code[i + 1] == '/'){
			while (code[i] != '\n') i++;
		}
		else if (code[i] == '<' && code[i + 1] == '>'){
			string temp = "";
			i += 2;
			bool cppStarted = false; // To check if cursor inside of '{}'
			while (i < code.length()){
				
				if (code[i] == '<' && code[i + 1] == '>') break;
				
				if (!cppStarted && code[i] == '\"'){
					temp += "\\\"";
				}
				else if (!cppStarted && code[i] == '\\'){
					temp += "\\\\";
				}
				else if (code[i] == '{'){
					cppStarted = true;
					temp += code[i];
				}
				else if (code[i] == '}'){
					cppStarted = false;
					temp += code[i];
				}
				else{
					temp += code[i];
				}
				i++;
				
			}
			i++;
			
			istringstream lss(temp);
			string line;
			
			while (getline(lss, line, '\n')) {
				string newLine = "";
				
				for (int j = 0; j < line.length(); j++){
					if (line[j] == '{'){
						j++;
						string variable = "";
						while (line[j] != '}'){
							variable += line[j];
							j++;
						}
						newLine += "\" + " + variable + " + \"";
					}else{
						newLine += line[j];
					}
				}
				
				newCode += "\"" + newLine + "\"\n";
//				cout<<newLine<<endl;
			}
			
			newCode.pop_back();
			newCode += ";";
			
		}else{
			if (code[i] == '@'){
				string type = "";
				i++;
				while(code[i] != ' '){
					type += code[i];
					i++;
				}
				if (!isComponent && type == "page"){
					newCode += "string";
					
					newCode += code[i];
					
					if (code[i] == ' '){
						string fnName = "";
						string fnNameExact = "";
						i++;
						bool isFoundName = false;
						
						while(code[i] != '{'){
							fnName += code[i];
							newCode += code[i];
							if (code[i] != '(' && !isFoundName) {
								fnNameExact += code[i];
							}else{
								isFoundName = true;
							}
							i++;
						}
						if (code[i - 1] != ')') fnName.pop_back();
						
						if (!isComponent){
							renderFunctions.emplace_back("string " + fnName + ";\n");
							renderFunctionCalls.emplace_back(fnNameExact);
						}else{
							componentFunctions.emplace_back("string " + fnName + ";\n");
						}
					}
					
				}
				else if (isComponent && type == "component"){
					newCode += "string";
					
					newCode += code[i];
					
					if (code[i] == ' '){
						string fnName = "";
						string fnNameExact = "";
						i++;
						bool isFoundName = false;
						
						while(code[i] != '{'){
							fnName += code[i];
							newCode += code[i];
							if (code[i] != '(' && !isFoundName) {
								fnNameExact += code[i];
							}else{
								isFoundName = true;
							}
							i++;
						}
						if (code[i - 1] != ')') fnName.pop_back();
						
						if (!isComponent){
							renderFunctions.emplace_back("string " + fnName + ";\n");
							renderFunctionCalls.emplace_back(fnNameExact);
						}else{
							componentFunctions.emplace_back("string " + fnName + ";\n");
						}
					}
					
				}
				else{
					cout<<"Error parsing please correct the indicator."<<endl;
					exit(1);
				}

			}
			
			newCode += code[i];
			
		}
		
	}
	
//	cout<<newCode<<endl;
	
	return newCode;
}


void generateParsedCode(string filename, string content){
	
	ofstream file(filename);
	
	string header = "#include \"../../src/include/pages.hpp\"\n#include \"../../src/include/components.hpp\"\n" + content;
	
	if (!file.is_open()) return;
	
	file << header << endl;
	
	file.close();
	
}

void generateParsedComponent(string filename, string content){
	
	ofstream file(filename);
	
	string header = "#include \"../../src/include/components.hpp\"\n\n" + content;
	
	if (!file.is_open()) return;
	
	file << header << endl;
	
	file.close();
	
}

void generatePages(){
	string pagesInclude = "#pragma once\n"
		"#ifndef PAGES_HPP\n"
		"#define PAGES_HPP\n"
		"#include <iostream>\n"
		"#include <unordered_map>\n"
		"#include <functional>\n"
		"#include \"response.hpp\"\n"
		"#include \"request.hpp\"\n"
		"using namespace std;\n\n";
	
	for (auto f : renderFunctions){
		pagesInclude += f + "\n";
	}
	
	pagesInclude += "#endif\n";
	
	ofstream pages("./src/include/pages.hpp");
	if (pages.is_open()){
		pages << pagesInclude <<endl;
	}
	pages.close();
}

void generateComponents(){
	string compInclude = "#pragma once\n"
		"#ifndef COMPONENTS_HPP\n"
		"#define COMPONENTS_HPP\n"
		"#include <iostream>\n"
		"using namespace std;\n\n";
	
	for (auto f : componentFunctions){
		compInclude += f + "\n";
	}
	
	compInclude += "#endif\n";
	
	ofstream components("./src/include/components.hpp");
	if (components.is_open()){
		components << compInclude <<endl;
	}
	components.close();
}

void generateRenders(){
	string renders = "#include \"pages.hpp\"\n"
	
	"static unordered_map<string, function<void(Request, Response)>> pages;\n"
	"static void initRenders(){\n";
	
	for (int i = 0; i < renderFunctions.size(); i++){
		renders += "pages[\"" + renderRoutes[i] + "\"] = [](Request req, Response res){ res.send(" + renderFunctionCalls[i] + "(req)); };\n";
	}
	
	renders += "}\n";
	
	ofstream render("./src/include/render.hpp");
	if (render.is_open()){
		render << renders <<endl;
	}
	render.close();
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

string toRoute(string filename){
	
	replace(filename, "./pages", "");
	
	if (filename.length() > 4){
		filename.resize(filename.length() - 4);
	}
	
//	cout<<filename<<endl;
	return filename;
}



int main(int argc, char **argv){
	time_t timestamp; 
	
	filesystem::path pagesDir = "./pages";
	filesystem::path componentsDir = "./components";
	string targetBuildPath = "./build";
	
	
	system("rm -rf ./build/pages/*.cpp");
	system("rm -rf ./build/components/*.cpp");
	
	// Translate all pages...
	for (auto& entry : filesystem::recursive_directory_iterator(pagesDir)){
		if (filesystem::is_regular_file(entry.path())){
			string cont = getFileContent(entry.path());
			string code = parseContent(cont, false);
			
			// Declare a variable of type time_t
			time(&timestamp);
			
			string filename = entry.path().filename().string();
			
			generateParsedCode(targetBuildPath + "/pages" + "/_" + to_string(timestamp) + "_" + filename, code);
			
			string filePath = entry.path().string();
			
			if (filename == "index.cpp"){
				replace(filePath, "index.cpp", "");
			}
			
			renderRoutes.emplace_back(toRoute(filePath));
			
			cout<<"Translated page : " << entry.path().string() << " -> " << toRoute(filePath)<<endl;
 		}
	}
	

	
	

	for (auto& entry : filesystem::recursive_directory_iterator(componentsDir)){
		if (filesystem::is_regular_file(entry.path())){
			string cont = getFileContent(entry.path());
			string code = parseContent(cont, true);
			
			// Declare a variable of type time_t
			time(&timestamp);

			string filename = entry.path().filename().string();
			
			generateParsedComponent(targetBuildPath + "/components" + "/_" + to_string(timestamp) + "_" + filename, code);
			
			cout<<"Translated component : " << entry.path().string() <<endl;
 		}
	}
	
	
	generateRenders();
	generatePages();
	generateComponents();
	
	string compiler = "g++ main.cpp ./src/include/*.cpp ./build/components/*.cpp ./build/pages/*.cpp -lSDL2main -lSDL2 -lSDL2_net -o main";
	
	cout<<"Compiling..."<<endl;
	system(compiler.c_str());
	cout<<"Server is starting..."<<endl;
	system("./main");
	
	system("rm -rf ./build/pages/*.cpp");
	system("rm -rf ./build/components/*.cpp");

	
	return 0;
}