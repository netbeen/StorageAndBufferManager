#pragma once
#include "Console.h"
#include <iostream>

struct BCB{
	bool isHead;
	bool isTrail;
	int frameID;
	int pageID;
	bool isWrite;
	BCB * previous;
	BCB * next;
};

class Hash_P2F{
public:
	Hash_P2F();
	void dropBCB(BCB * const victim);
	bool findPage(const int);
	void insertBCB(const int frameID, const int pageID, const bool isWrite);
	BCB * locateNode(const int pageID);
private:
	int hash(const int) const;
	void init();
	BCB * searchPtr;
	BCB * hashTable[BUFFERSIZE];
};

