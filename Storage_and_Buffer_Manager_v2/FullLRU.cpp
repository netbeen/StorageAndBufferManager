#include "FullLRU.h"

using namespace std;

FullLRU::FullLRU(){
	init();
}

void FullLRU::init(){
	initHeadAndTrail();

	cout << "#   (4/5) Full LRU link list initialize cpmpeted.          #" << endl;
}

//Search the specific node in LRU link list with the pageID, and adjust it into the trail.
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
