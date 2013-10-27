#pragma once
#include "LRU.h"

class FullLRU :public LRU{
public:
	FullLRU();
	void adjustLRU(const int);
private:
	void init();
	
};