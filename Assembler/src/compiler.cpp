#include "main.h"

using namespace std;

string jmpNames[65536];
string jmpValues[65536];
int jmpSize = 0;

uint16_t cycle = 0x0000;

ofstream outFilee("output.hex");

void writeToFilee(string whatToWrite){
	if(whatToWrite != "") outFilee << whatToWrite;
}

string fixHexToString(string hex){
	if(hex.size() <= 1){
		return "000" + hex;
	}
	if(hex.size() <= 2){
		return "00" + hex;
	}
	if(hex.size() <= 3){
		return "0" + hex;
	}
	if(hex.size() <= 4){
		return hex;
	}
	return "0000";
}

char getFirstReg(string part){
	if(part[4] == 'a') return '1';
	if(part[4] == 'b') return '2';
	if(part[4] == 'c') return '3';
	if(part[4] == 'd') return '4';
	return '0';
}

char getSecondReg(string part){
	if(part[7] == 'a') return '1';
	if(part[7] == 'b') return '2';
	if(part[7] == 'c') return '3';
	if(part[7] == 'd') return '4';
	return '0';
}

string jump(string part){
	for(int i=0; i<jmpSize; i++){
		if(jmpNames[i] == part.substr(4, sizeof(part))){
			return fixHexToString(jmpValues[i]);
			break;
		}
	}
	return "";
}

string jei(string part){
	for(int i=0; i<jmpSize; i++){
		if(jmpNames[i] == part.substr(3, sizeof(part))){
			return fixHexToString(jmpValues[i]);
			break;
		}
	}
	return "";
}

string inti(string part){
	//cout << part.substr(4, sizeof(part)) << endl;
	for(int i=0; i<jmpSize; i++){
		//cout << fixHexToString(jmpValues[i]) << endl;
		//cout << jmpNames[i] << endl;
		//cout << part.substr(4, sizeof(part)) << endl;
		if(jmpNames[i] == part.substr(4, sizeof(part))){
			//cout << "INT" << endl;
			return fixHexToString(jmpValues[i]);
			break;
		}
	}
	return "";
}

string convert(string part){
	string output;
	if(part.find(':') != string::npos){
		jmpNames[jmpSize] = part.substr(0, part.find(':'));
		jmpValues[jmpSize] = to_string(cycle);
		jmpSize++;
		return output;
	}
	if(part.substr(0, 3) == "nop"){
		output = "0000000000";
		return output;
	}
	if(part.substr(0, 3) == "hlt"){
		output = "0100000000";
		return output;
	}
	if(part.substr(0, 3) == "add"){
		output += "02";
		output += getFirstReg(part);
		output += part.substr(9, 11);
		output += "00000";
		return output;
	}
	if(part.substr(0, 3) == "adr"){
		output += "03";
		output += getFirstReg(part);
		output += getSecondReg(part);
		output += "000000";
		return output;
	}
	if(part.substr(0, 3) == "dec"){
		output += "04";
		output += getFirstReg(part);
		output += part.substr(9, 11);
		output += "00000";
		return output;
	}
	if(part.substr(0, 3) == "der"){
		output += "05";
		output += getFirstReg(part);
		output += getSecondReg(part);
		output += "000000";
		return output;
	}
	if(part.substr(0, 3) == "set"){
		output += "06";
		output += getFirstReg(part);
		output += part.substr(9, 11);
		output += "00000";
		return output;
	}
	if(part.substr(0, 3) == "jmp"){
		output += "07";
		output += jump(part);
		output += "0000";
		return output;
	}
	if(part.substr(0, 3) == "jmr"){
		output += "08";
		output += getFirstReg(part);
		output += "0000000";
		return output;
	}
	if(part.substr(0, 3) == "jmz"){
		output += "09";
		output += jump(part);
		output += "0000";
		return output;
	}
	if(part.substr(0, 3) == "jmo"){
		output += "0a";
		output += jump(part);
		output += "0000";
		return output;
	}
	if(part.substr(0, 3) == "cmp"){
		output += "0b";
		output += getFirstReg(part);
		output += part.substr(9, 11);
		output += "000";
		return output;
	}
	if(part.substr(0, 3) == "cmr"){
		output += "0c";
		output += getFirstReg(part);
		output += getSecondReg(part);
		output += "000000";
		return output;
	}
	if(part.substr(0, 2) == "je"){
		output += "0d";
		output += jei(part);
		output += "0000";
		return output;
	}
	if(part.substr(0, 3) == "inb"){
		output += "0e";
		output += getFirstReg(part);
		output += "0000000";
		return output;
	}
	if(part.substr(0, 3) == "oub"){
		output += "0f";
		output += part.substr(6, 8);
		output += "0000";
		return output;
	}
	if(part.substr(0, 3) == "our"){
		output += "10";
		output += getFirstReg(part);
		output += "0000000";
		return output;
	}
	if(part.substr(0, 3) == "sin"){
		output += "11";
		output += getFirstReg(part);
		output += "0000000";
		return output;
	}
	if(part.substr(0, 3) == "sou"){
		output += "12";
		output += part.substr(6, 8);
		output += "0000";
		return output;
	}
	if(part.substr(0, 3) == "sor"){
		output += "13";
		output += getFirstReg(part);
		output += "0000000";
		return output;
	}
	if(part.substr(0, 3) == "mem"){
		output += "14";
		output += getFirstReg(part);
		output += part.substr(9, 11);
		output += "000";
		return output;
	}
	if(part.substr(0 , 3) == "mer"){
		output += "15";
		output += getFirstReg(part);
		output += getSecondReg(part);
		output += "000000";
		return output;
	}
	if(part.substr(0 ,3) == "lem"){
		output += "16";
		output += getFirstReg(part);
		output += part.substr(9, 11);
		output += "000";
		return output;
	}
	if(part.substr(0, 3) == "ler"){
		output += "17";
		output += getFirstReg(part);
		output += getSecondReg(part);
		output += "000000";
		return output;
	}
	if(part.substr(0, 3) == "vem"){
		output += "18";
		output += part.substr(6, 4);
		output += part.substr(14, 14);
		//output += "0000";
		return output;
	}
	if(part.substr(0, 3) == "ver"){
		output += "19";
		output += getFirstReg(part);
		output += part.substr(9, 11);
		output += "000";
		return output;
	}
	if(part.substr(0 , 3) == "vrm"){
		output += "1a";
		output += getFirstReg(part);
		output += part.substr(9, 11);
		output += "000";
		return output;
	}
	if(part.substr(0, 3) == "vrr"){
		output += "1b";
		output += getFirstReg(part);
		output += getSecondReg(part);
		output += "000000";
		return output;
	}
	if(part.substr(0, 3) == "ret"){
		output += "1c00000000";
		return output;
	}
	if(part.substr(0, 3) == "int"){
		output += "1d";
		//cout << inti(part) << endl;
		output += inti(part);
		output += "0000";
		return output;
	}
	return "";
}

void compileFromParsed(){
	int cycl = 0;
	ifstream inputFile;
	string inp;
	inputFile.open("assembler.tmp");
	writeToFilee("v3.0 hex words plain\n");
	if(inputFile.is_open()){
		while (inputFile){
			cycl++;
			getline(inputFile, inp);
			if(convert(inp) != ""){
				//cout << convert(inp) << endl;
				writeToFilee(convert(inp) + " ");
				if(cycl == 9){
					writeToFilee(" \n");
					cycl = 1;
				}
			}
			cycle += 0x0001;
		}
	}
}
