#include "main.h"

using namespace std;

ofstream outFile("assembler.tmp");;

int isInside(const std::string & str, char c){
	//cout << str.find(c) << endl;
    	return str.find(c);
}

void writeToFile(string whatToWrite){
	if(whatToWrite != "") outFile << whatToWrite << endl;
}

void prepairFile(string fileName){
	ifstream hxFile;
	int cycle = 0;
	bool isComment = false;
	hxFile.open(fileName);
	while(hxFile.is_open() && hxFile.good()){
		cycle++;
		string inp;
		getline(hxFile, inp);
		if(isInside(inp, ';') == 0){
			isComment = true;
		}
		if(isInside(inp, ';') > 0){
			string newInp = inp.substr(0, isInside(inp, ';')-1);
			isComment = true;
			//cout << newInp << endl;
			writeToFile(newInp);
		}
		//if(inp.find(' ') != string::npos){
		//	isComment = true;
		//}
		if(isComment == false){
			//cout << inp << endl;
			writeToFile(inp);
		}
		if(isComment == true){
			isComment = false;
		}
	}
	return;
}
