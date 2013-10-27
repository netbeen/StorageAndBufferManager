#include "FullLRU.h"

using namespace std;

FullLRU::FullLRU(){
	init();
}

void FullLRU::init(){
	initHeadAndTrail();

	cout << "Full LRU link list initialize cpmpeted." << endl;
}

void FullLRU::adjustLRU(const int pageID){
	current = &trail;
	while(current ->lessRecent ->isHead == false){
		current = current ->lessRecent;
		if (current ->pageID == pageID){
			dropNode(current);
			insertNodeOnTrail(current);
			return;
		}
	}
	exit(1);
}
