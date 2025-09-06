#include "aerox.hpp"

string Aerox::parseContent(string file, string code, bool isComponent = false){

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