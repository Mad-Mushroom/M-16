#include "main.h"

using namespace std;

bool exiting = false;

int line = 0;
int cycle = 0x0000;

string jmpNames[65536];
string jmpValues[65536];
int jmpSize = 0;

void Err(string errMsg){
	cout << "Error! " << errMsg << endl;
	exiting = true;
}

string getRegister(string inp){
	if(inp.find("&a") < 6) return "1";
	if(inp.find("&b") < 6) return "2";
	if(inp.find("&c") < 6) return "3";
	if(inp.find("&d") < 6) return "4";
	Err("Could not find needed Register in line " + to_string(line) + ": " + inp);
	return "";
}

string getSRegister(string inp){
	if(inp.find("&a") != string::npos) inp = inp.substr(inp.find("&a"), inp.size());
	if(inp.find("&b") != string::npos) inp = inp.substr(inp.find("&b"), inp.size());
	if(inp.find("&c") != string::npos) inp = inp.substr(inp.find("&c"), inp.size());
	if(inp.find("&d") != string::npos) inp = inp.substr(inp.find("&d"), inp.size());
	if(inp.find("&a") != string::npos) return "1";
	if(inp.find("&b") != string::npos) return "2";
	if(inp.find("&c") != string::npos) return "3";
	if(inp.find("&d") != string::npos) return "4";
	Err("Could not find needed Register in line " + to_string(line) + ": " + inp);
	return "";
}

string getHexValue(string inp){
	if(inp.find("0x")) return inp.substr(inp.find("0x")+2, 4);
	Err("Could not find needed Hex Value in line " + to_string(line) + ": " + inp);
	return "";
}

string hexToStr(int hxValue){
	ostringstream tmp;
	tmp << hex << hxValue;
	string hexStr = tmp.str();
	if(hexStr.length() <= 1) return "000" + hexStr;
	if(hexStr.length() <= 2) return "00" + hexStr;
	if(hexStr.length() <= 3) return "0" + hexStr;
	return hexStr;
}

string jmp(string inp){
	for(int i=0; i<jmpSize; i++){
		if(inp.find(jmpNames[i]) != string::npos){
			return jmpValues[i];
			break;
		}
	}
	return "";
}

string assemble(string inp){
	if(inp == "") return "";
	if(inp.find(";") == 0) return "";
	if(inp.find(";") > 0) inp = inp.substr(0, inp.find(";"));

	if(inp.find(":") != string::npos){
		jmpNames[jmpSize] = inp.substr(0, inp.find(":"));
		jmpValues[jmpSize] = hexToStr(cycle);
		jmpSize++;
		return "";
	}

	if(inp.find("nop") != string::npos) return "0000000000";
	if(inp.find("hlt") != string::npos) return "0100000000";
	if(inp.find("add") != string::npos) return "02" + getRegister(inp) + getHexValue(inp) + "000";
	if(inp.find("adr") != string::npos) return "03" + getRegister(inp) + getSRegister(inp) + "000000";
	if(inp.find("dec") != string::npos) return "04" + getRegister(inp) + getHexValue(inp) + "000";
	if(inp.find("der") != string::npos) return "05" + getRegister(inp) + getSRegister(inp) + "000000";
	if(inp.find("set") != string::npos) return "06" + getRegister(inp) + getHexValue(inp) + "000";
	if(inp.find("jmp") != string::npos) return "07" + jmp(inp) + "0000";
	if(inp.find("jmr") != string::npos) return "08" + getRegister(inp) + "0000000";
	if(inp.find("jmz") != string::npos) return "09" + jmp(inp) + "0000";
	if(inp.find("jmo") != string::npos) return "0a" + jmp(inp) + "0000";
	if(inp.find("cmp") != string::npos) return "0b" + getRegister(inp) + getHexValue(inp) + "000";
	if(inp.find("cmr") != string::npos) return "0c" + getRegister(inp) + getSRegister(inp) + "000000";
	if(inp.find("je ") != string::npos) return "0d" + jmp(inp) + "0000";
	if(inp.find("inb") != string::npos) return "0e" + getRegister(inp) + "0000000";

	Err("Could not assemble line " + to_string(line) + ": " + inp);
	return "";
}

int main(int argc, char* argv[]){
	ifstream inputFile(argv[1]);
	while(inputFile.is_open() && inputFile.good() && !exiting){
		if(exiting) break;
		line++;
		string inp;
		getline(inputFile, inp);
		if(assemble(inp) != "") cout << assemble(inp) << endl;
		cycle += 0x0001;
	}
	return 0;
}
