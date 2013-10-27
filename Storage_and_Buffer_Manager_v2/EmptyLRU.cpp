#include "EmptyLRU.h"

using namespace std;

EmptyLRU::EmptyLRU(){
	availableNodeCount = 0;
	init();
}

//Initialize the LRU link list.
void EmptyLRU::init(){
	
	initHeadAndTrail();
	
	for(int i = 0; i < BUFFERSIZE; i++){
		current = new LRUElement;
		current ->frameID = i;
		current ->isHead = false;
		current ->isTrail = false;
		insertNodeOnTrail(current);
	}

	availableNodeCount = BUFFERSIZE;

	cout << "Empty LRU link list initialize cpmpeted." << endl;
}

int EmptyLRU::getAvailableNodeCount() const{
	return availableNodeCount;
}	

void EmptyLRU::setAvailableNodeCountMinusOne(){
	availableNodeCount --;
}