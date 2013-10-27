#pragma once
#include "LRU.h"

class EmptyLRU :public LRU{
public:
	EmptyLRU();
	int getAvailableNodeCount() const;
	void setAvailableNodeCountMinusOne();
private:
	void init();
	int availableNodeCount;
};