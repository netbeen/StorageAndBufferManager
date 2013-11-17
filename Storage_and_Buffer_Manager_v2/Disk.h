#pragma once
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;

const int MAXPAGES = 50100;
const int PAGESIZE = 4096;

class Disk{
public:
	Disk();
	~Disk();
	void inputProcess(const int pageID);
	void outputProcess(const int pageID);
private:
	void writeLog(const int pageID);
	void searchIndex();
	void searchPageTable();
	void init();
	char * frame;
	ifstream input;
	ofstream output;
	ofstream log;
};