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
	cout << "#   (5/5) Hash table of page to frame initialize competed. #" << endl;
}

//Return whether the specific page with the pageID exist in the buffer.
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

//Calculate the hash.
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

//Find where the node with the pageID is.
BCB * Hash_P2F::locateNode(const int pageID){
	int hashResult = hash(pageID);
	BCB * searchPtr = hashTable[hashResult];
	while(searchPtr ->next ->isTrail != true){
		searchPtr = searchPtr ->next;
		if(searchPtr ->pageID == pageID){
			return searchPtr;
		}
	}
}

//Cut the two pointer of the node.
void Hash_P2F::dropBCB(BCB * const victim){
	victim ->previous ->next = victim ->next;
	victim ->next ->previous = victim ->previous;
}