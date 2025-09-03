#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <ctime>
#include <unordered_map>
#include "src/ext/json.hpp"

using namespace std;

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

string parseContent(string file, string code, bool isComponent = false){

	string newCode = "";
		
	int title = 0;
	int description = 0;
	int page = 0;
	
	string fnNameExact = "";
	
	int lines = 0;
	
	for (int i = 0; i < code.length(); i++){
		
		if (code[i] == '/' && code[i + 1] == '/'){
			while (code[i] != '\n') i++;
			lines++;
		}
		else if (code[i] == '\n'){
			lines++;
			newCode += code[i];
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
				else if (code[i] == '\n'){
					lines++;
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
//				lines++;
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

				if (!isComponent){
					// To handle @page
					if (type == "page"){
						
						if (page > 0){
							errors.emplace_back(file + " Error on reusing @page indicator at line " + to_string(lines) + ". Page already declared.");
							
						}else{
							page = 1;
						}
						
						newCode += "string";
						newCode += code[i];
						
						
						
						
						if (code[i] == ' '){
							string fnName = "";
							
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
							renderFunctions.emplace_back("string " + fnName + ";\n");
							renderFunctionCalls.emplace_back(fnNameExact);
						}
					
					}
					// To handle @title
					else if (type == "title"){
						
						if (title > 0){
							errors.emplace_back(file + " Error on reusing @title indicator at line " + to_string(lines) + ". Meta title is already declared.");
							
						}else{
							title = 1;
						}
						
						newCode += "__title__";
						
						while(code[i] != '\n') {
							newCode += code[i];
							i++;
						}
						lines++;
					}
					// To handle @description
					else if (type == "description"){
						if (description > 0){
							errors.emplace_back(file + " Error on reusing @description indicator at line " + to_string(lines) + ". Meta description is already declared.");
							
						}else{
							description = 1;
						}
						
						newCode += "__description__";
						
						while(code[i] != '\n') {
							newCode += code[i];
							i++;
						}
						lines++;
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

						componentFunctions.emplace_back("string " + fnName + ";\n");
					}
					
				}
				else{
					if (!isComponent && type == "component"){
						errors.emplace_back(file + " Component cannot be created on non-component file at line " + to_string(lines) + ". Create components on ./components directory.");
					}
					if (isComponent && type == "page"){
						errors.emplace_back(file + " Page cannot be created on non-page file at line " + to_string(lines) + ". Create pages on ./pages directory.");
					}
					
					cout<<"Error parsing please correct the indicator."<<endl;
					exit(1);
				}
				// Setting metadata for a page route.
			}
			
			newCode += code[i];
			
		}
		
	}
		
	return newCode;
}


void generateParsedCode(string filename, string content){
	
	ofstream file(filename);
	
	string header = "#include \"../../src/include/pages.hpp\"\n"
					"#include \"../../src/include/components.hpp\"\n" 
					"#include \"../../src/include/metadata.hpp\"\n\n"+ content;
	
	if (!file.is_open()) return;
	
	file << header << endl;
	
	file.close();
	
}

void generateParsedComponent(string filename, string content){
	
	ofstream file(filename);
	
	string header = "#include \"../../src/include/components.hpp\"\n\n" 
					"#include \"../../src/include/document.hpp\"\n\n" + content;
	
	
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
//		"#include \"metadata.hpp\"\n"
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

void generateMetadata(){
	string md = "#ifndef METADATA_HPP\n"
				"#define METADATA_HPP\n"
				"#include <iostream>\n"
				"using namespace std;\n"
				"extern string __title__;\n"
				"extern string __description__;\n"
				"#endif\n";
	
	ofstream metadata("./src/include/metadata.hpp");
	if (metadata.is_open()){
		metadata << md <<endl;
	}
	metadata.close();
}

void generateComponents(){
	string compInclude = "// This file is generated by Aerox dynamically while building\n"
		"#pragma once\n"
		"#ifndef COMPONENTS_HPP\n"
		"#define COMPONENTS_HPP\n"
		"#include <iostream>\n"
		"#include \"metadata.hpp\"\n"
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
	
	
	string renders = "// This file is generated by Aerox dynamically while building\n"
	"#include \"pages.hpp\"\n"
	"#include \"components.hpp\"\n"
	"#include \"../ext/json.hpp\"\n"
	"static unordered_map<string, function<void(Request, Response)>> pages;\n"
	"static string sendNavigationResponse(string page){\n"
	"\tnlohmann::json data;\n"
	"\tdata[\"body\"] = page;\n"
	"\tnlohmann::json meta;\n"
	"\tmeta[\"title\"] = __title__;\n"
	"\tmeta[\"description\"] = __description__;\n"
	"\tdata[\"meta\"] = meta;\n"
	"\treturn data.dump();\n"
	"}\n"
	"static void initRenders(){\n";
	
	for (int i = 0; i < renderFunctions.size(); i++){
		renders += "\tpages[\"" + renderRoutes[i] + "\"] = [](Request req, Response res){\n"
					"\t\tstring page = " + renderFunctionCalls[i] + "(req);\n"
					"\t\tstring root = MainRoot(page);\n"
					"\t\tif (req.query[\"navigate\"] != \"\")\n"
					"\t\t\tres.sendJSON(sendNavigationResponse(page));\n"
					"\t\telse\n"
					"\t\t\tres.send(root);\n"
					"\t__title__ = \"\";\n"
					"\t__description__ = \"\";\n"
					"\t};\n\n";
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
	
	
	filesystem::path pagesDir = "./pages";
	filesystem::path componentsDir = "./components";
	string targetBuildPath = "./.aerox";
	
	
	cout<<"Aerox 1.1"<<endl;
	
	int id = 0;
	
	// Parse and build all the pages...
	for (auto& entry : filesystem::recursive_directory_iterator(pagesDir)){
		if (filesystem::is_regular_file(entry.path())){
			id++; // File id
			
			string filename = entry.path().filename().string(); // Get filename
			string filePath = entry.path().string(); // Get path/to/file
			
			string code = getFileContent(entry.path());
			string parsedCode = parseContent(filePath, code, false);
		
			
			
			generateParsedCode(targetBuildPath + "/pages" + "/_" + to_string(id) + "_" + filename, parsedCode);
			
			
			
			if (filename == "index.cpp"){
				replace(filePath, "index.cpp", "");
			}
			
			renderRoutes.emplace_back(toRoute(filePath));
			
			if (errors.size() < 1) cout<<"[√] Translated page : " << entry.path().string() << " -> " << toRoute(filePath)<<endl;
 		}
	}
	

	// Parse and build all components...
	for (auto& entry : filesystem::recursive_directory_iterator(componentsDir)){
		if (filesystem::is_regular_file(entry.path())){
			id++; // File id
			
			
			string filename = entry.path().filename().string(); // Get filename
			string filePath = entry.path().string(); // Get path/to/file
			
			string code = getFileContent(entry.path());
			string parsedCode = parseContent(filePath, code, true);
			
			generateParsedComponent(targetBuildPath + "/components" + "/_" + to_string(id) + "_" + filename, parsedCode);
			
			if (errors.size() < 1) cout<<"[√] Translated component : " << entry.path().string() <<endl;
 		}
	}
	
	if (errors.size() > 0){
		for (auto error : errors){
			cout<<error<<endl;
		}
		cout<<"Building terminated unsuccesfully..."<<endl;
		exit(1);
	}else{
		cout<<"Pages & components translated successfuly..."<<endl;
	}
	
//	nlohmann::json obj;
//	
//	obj["title"] = "Hello world";
//	obj["description"] = "description";
//	cout<<obj.dump()<<endl;
	
	generateRenders();
	generatePages();
	generateComponents();
	generateMetadata();
//	
	string compiler = "g++ main.cpp ./src/*/*.cpp ./.aerox/*/*.cpp -lSDL2main -lSDL2 -lSDL2_net -o main";
	
	cout<<"Compiling..."<<endl;
	system(compiler.c_str());
	cout<<"Server is starting..."<<endl;
	system("./main");
	
	return 0;
}