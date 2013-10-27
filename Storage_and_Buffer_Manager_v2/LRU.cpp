#include "LRU.h"

//Set the two pointer of each nodes.
void LRU::initHeadAndTrail(){
	head.isHead = true;
	head.isTrail = false;
	head.lessRecent = nullptr;
	head.moreRecent = &trail;

	trail.isTrail = true;
	trail.isHead = false;
	trail.lessRecent = &head;
	trail.moreRecent = nullptr;
}

//Insert node.
void LRU::insertNodeOnTrail(LRUElement * const newNode){
	newNode ->moreRecent = &trail;
	newNode ->lessRecent = trail.lessRecent;

	newNode ->lessRecent ->moreRecent = newNode;
	trail.lessRecent = newNode;
}

//Cut the two pointer of the node.
void LRU::dropNode(LRUElement * const dropPtr){
	dropPtr ->lessRecent ->moreRecent = dropPtr ->moreRecent;
	dropPtr ->moreRecent ->lessRecent = dropPtr ->lessRecent;
}

//Get an empty node.
LRUElement * LRU::returnTheOneBeforeTrail(){
	LRUElement * returnPtr;
	returnPtr = trail.lessRecent;
	return returnPtr;
}

//Decide the victim.
LRUElement * LRU::returnTheOneAfterHead(){
	LRUElement * returnPtr;
	returnPtr = head.moreRecent;
	return returnPtr;
}