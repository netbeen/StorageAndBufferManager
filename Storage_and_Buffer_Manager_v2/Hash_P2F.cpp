#include "Hash_P2F.h"

using namespace std;

Hash_P2F::Hash_P2F(){
	init();
}

void Hash_P2F::init(){
	for(int i = 0; i < BUFFERSIZE; i ++){
		BCB * newHead = new BCB;
		BCB * newTrail = new BCB;
		newHead ->isHead = true;
		newHead ->isTrail =false;
		newHead ->previous = nullptr;
		newHead ->next = newTrail;

		newTrail ->isHead = false;
		newTrail ->isTrail = true;
		newTrail ->previous = newHead;
		newTrail ->next = nullptr;

		hashTable[i] = newHead;
	}
	cout << "Hash table, for page to frame, initialize competed." << endl;
}

bool Hash_P2F::findPage(const int pageID){
	int hashResult = hash(pageID);
	searchPtr = hashTable[hashResult];
	while(searchPtr ->next ->isTrail != true){
		searchPtr = searchPtr ->next;
		if (searchPtr ->pageID == pageID)
			return true;
	}
	return false;
}

int Hash_P2F::hash(const int pageID) const{
	return (pageID % BUFFERSIZE);
}

void Hash_P2F::insertBCB(const int frameID, const int pageID, const bool isWrite){
	int hashResult = hash(pageID);
	BCB * inserting = new BCB;
	inserting ->frameID = frameID;
	inserting ->pageID = pageID;
	inserting ->isWrite = isWrite;
	inserting ->isHead = false;
	inserting ->isTrail =false;
	
	inserting ->previous = hashTable[hashResult];
	inserting ->next = hashTable[hashResult] ->next;
	inserting ->next ->previous = inserting;
	hashTable[hashResult] ->next = inserting;
}

BCB * Hash_P2F::locateNode(const int pageID){
	int hashResult = hash(pageID);
	BCB * searchPtr = hashTable[hashResult];
	while(searchPtr ->next ->isTrail != true){
		searchPtr = searchPtr ->next;
		if(searchPtr ->pageID == pageID){
			return searchPtr;
		}
	}
	exit(2);
}

void Hash_P2F::dropBCB(BCB * const victim){
	victim ->previous ->next = victim ->next;
	victim ->next ->previous = victim ->previous;
}

bool Hash_P2F::wasWritten(const int pageID){
	int hashResult = hash(pageID);
	searchPtr = hashTable[hashResult];
	while(searchPtr ->next ->isTrail != true){
		searchPtr = searchPtr ->next;
		if (searchPtr ->pageID == pageID)
			return (searchPtr ->isWrite);
	}
	exit(3);
}