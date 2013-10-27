#include "LRU.h"

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

void LRU::insertNodeOnTrail(LRUElement * const newNode){
	newNode ->moreRecent = &trail;
	newNode ->lessRecent = trail.lessRecent;

	newNode ->lessRecent ->moreRecent = newNode;
	trail.lessRecent = newNode;
}

void LRU::dropNode(LRUElement * const dropPtr){
	dropPtr ->lessRecent ->moreRecent = dropPtr ->moreRecent;
	dropPtr ->moreRecent ->lessRecent = dropPtr ->lessRecent;
}

LRUElement * LRU::returnTheOneBeforeTrail(){
	LRUElement * returnPtr;
	returnPtr = trail.lessRecent;
	return returnPtr;
}

LRUElement * LRU::returnTheOneAfterHead(){
	LRUElement * returnPtr;
	returnPtr = head.moreRecent;
	return returnPtr;
}