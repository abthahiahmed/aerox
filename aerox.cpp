#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <ctime>
#include <unordered_map>

using namespace std;

struct MetaData { // Structure for metadata
	string title;
	string description;
};

vector<string> renderFunctions;
vector<string> renderFunctionCalls;
vector<string> renderRoutes;
unordered_map<string, MetaData> metaData;

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
		
	string title = "";
	string description = "";
	string fnNameExact = "";
	
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

				if (!isComponent){
					// To handle @page
					if (type == "page"){
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
						
						newCode += "__title__";
						
						while(code[i] != '\n') {
							newCode += code[i];
							i++;
						}
						
					}
					// To handle @description
					else if (type == "description"){
						
						newCode += "__description__";
						
						while(code[i] != '\n') {
							newCode += code[i];
							i++;
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

						componentFunctions.emplace_back("string " + fnName + ";\n");
					}
					
				}
				else{
					cout<<"Error parsing please correct the indicator."<<endl;
					exit(1);
				}
				// Setting metadata for a page route.
			}
			
			newCode += code[i];
			
		}
		
	}

//	if (!isComponent && fnNameExact != ""){
//		metaData[fnNameExact] = {title, description};
//	}
//	cout<<newCode<<endl;
	
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
	"static unordered_map<string, function<void(Request, Response)>> pages;\n"
	"static void initRenders(){\n";
	
	for (int i = 0; i < renderFunctions.size(); i++){
		renders += "\tpages[\"" + renderRoutes[i] + "\"] = [](Request req, Response res){\n"
//					"\t\t__title__ = \"" + metaData[renderFunctionCalls[i]].title + "\";\n"
//					"\t\t__description__ = \"" + metaData[renderFunctionCalls[i]].description + "\";\n"
					"\t\tstring page = " + renderFunctionCalls[i] + "(req);\n"
					"\t\tstring root = MainRoot(page);\n"
					"\t\tres.send(root);\n"
					"__title__ = \"\";\n"
					"__description__ = \"\";\n"
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
			id++;
			string cont = getFileContent(entry.path());
			string code = parseContent(cont, false);
		
			string filename = entry.path().filename().string();
			
			generateParsedCode(targetBuildPath + "/pages" + "/_" + to_string(id) + "_" + filename, code);
			
			string filePath = entry.path().string();
			
			if (filename == "index.cpp"){
				replace(filePath, "index.cpp", "");
			}
			
			renderRoutes.emplace_back(toRoute(filePath));
			
			cout<<"[√] Translated page : " << entry.path().string() << " -> " << toRoute(filePath)<<endl;
 		}
	}
	

	// Parse and build all components...
	for (auto& entry : filesystem::recursive_directory_iterator(componentsDir)){
		if (filesystem::is_regular_file(entry.path())){
			id++;
			string cont = getFileContent(entry.path());
			string code = parseContent(cont, true);
			

			string filename = entry.path().filename().string();
			
			generateParsedComponent(targetBuildPath + "/components" + "/_" + to_string(id) + "_" + filename, code);
			
			cout<<"[√] Translated component : " << entry.path().string() <<endl;
 		}
	}
	
	
	generateRenders();
	generatePages();
	generateComponents();
	generateMetadata();
	
	string compiler = "g++ main.cpp ./src/*/*.cpp ./.aerox/*/*.cpp -lSDL2main -lSDL2 -lSDL2_net -o main";
	
	cout<<"Compiling..."<<endl;
	system(compiler.c_str());
	cout<<"Server is starting..."<<endl;
	system("./main");
	
	return 0;
}