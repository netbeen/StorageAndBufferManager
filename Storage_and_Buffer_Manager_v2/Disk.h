#pragma once
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;

const int MAXPAGES = 50000;
const int PAGESIZE = 4096;
const int NTFSINDEXPAGESIZE = 512;
const int NTFSPAGETABLESIZE = 4096;

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
	ifstream index;
	ifstream pageTable;
	ofstream output;
	ofstream log;
};