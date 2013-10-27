#include "Console.h"

using namespace std;

Console::Console(){
	init();
}

void Console::init(){
	ifstream inFile("data-5w-50w-zipf.txt");
	string tmp,tmpPre,tmpSuf;
	int commaIndex,dataRequestIndex = 0;
	while (dataRequestIndex < TESTCOUNT){
		getline(inFile,tmp);
		commaIndex = tmp.find(",");
		tmpPre = tmp.substr(0,commaIndex);
		tmpSuf = tmp.substr(commaIndex + 1);
		if (tmpPre == "1")
			arrayOfDataRequest[dataRequestIndex].isWrite = true;
		else
			arrayOfDataRequest[dataRequestIndex].isWrite = false;
		arrayOfDataRequest[dataRequestIndex].pageID = atoi(tmpSuf.c_str());
		dataRequestIndex ++;
	}
	cout << "Console initialization competed." << endl;
}