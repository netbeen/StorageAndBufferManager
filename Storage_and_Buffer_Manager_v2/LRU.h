#pragma once
#include <iostream>
#include "Console.h"

struct LRUElement{
	bool isHead;
	bool isTrail;
	int frameID;
	int pageID;
	LRUElement * moreRecent;
	LRUElement * lessRecent;
};

class LRU{
public:
	virtual void init() = 0;
	LRUElement * returnTheOneBeforeTrail();
	LRUElement * returnTheOneAfterHead();
	void insertNodeOnTrail(LRUElement * const);
	void dropNode(LRUElement * const);
protected:
	
	void initHeadAndTrail();
	LRUElement head;
	LRUElement trail;
	LRUElement * current;
};

