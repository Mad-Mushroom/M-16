#include "main.h"

using namespace std;

string fileName;

void Err(string ErrMsg){
	cout << "Program Error!" << endl << endl;;
	cout << "Details:" << endl;
	cout << ErrMsg << endl;
}

void assemble(){
	prepairFile(fileName);
	compileFromParsed();
}

int main(int argc, char* argv[]){
	if((argc-1) > 0){
		//cout << argv[1] << endl;
		fileName = argv[1];
		assemble();
	}else{
		cout << "File? ";
		cin >> fileName;
		cout << "" << endl;
		assemble();
	}
	return 0;
}
