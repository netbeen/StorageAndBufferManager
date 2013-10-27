#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Disk.h"

const int BUFFERSIZE = 1024;	//default BUFFERSIZE is 1024
const int FRAMESIZE = PAGESIZE;
const int TESTCOUNT = 500000;

struct dataRequest{
	bool isWrite;
	int pageID;
};

class Console{
public:
	Console();
	dataRequest arrayOfDataRequest[TESTCOUNT];
private:
	void init();
};

