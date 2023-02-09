#include "main.h"

using namespace std;

string fileName;

void Err(string ErrMsg){
	cout << "Program Error!" << endl << endl;;
	cout << "Details:" << endl;
	cout << ErrMsg << endl;
}

int main(int argc, char* argv[]){
	if((argc-1) > 0){
		//cout << argv[1] << endl;
		fileName = argv[1];
		prepairFile(fileName);
	}else{
		Err("No Argument");
	}
	return 0;
}
