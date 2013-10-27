#pragma once
#include <fstream>
#include <iostream>

using namespace std;

const int MAXPAGES = 50000;
const int PAGESIZE = 4096;

class Disk{
public:
	Disk();
	void inputProcess(const int pageID);
	void outputProcess(const int pageID);
private:
	void init();
	char * frame;
	ifstream input;
	ofstream output;
};

