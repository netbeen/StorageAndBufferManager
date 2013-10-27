#include <time.h>
#include <iomanip>
#include "Console.h"
#include "EmptyLRU.h"
#include "FullLRU.h"
#include "Hash_P2F.h"

using namespace std;

/*************************************************
Author: Yang Yang
Date&Time: 2013-10-27 23:38
Version: 2.1
*************************************************/
int main(){
	cout << "=================Storage and Buffer Manager=================" << endl;
	Console console = Console();
	Disk disk = Disk();
	EmptyLRU emptyLRU = EmptyLRU();
	FullLRU fullLRU = FullLRU();
	Hash_P2F hash_p2f = Hash_P2F();

	int hitCount = 0;
	int IOCount = 0;

	cout << "====================Now Start Simulating====================" << endl;
	clock_t startTime = clock();

	for (int requestIndex = 0; requestIndex < TESTCOUNT; requestIndex ++){		
		int pageID = console.arrayOfDataRequest[requestIndex].pageID;
		bool isWrite = console.arrayOfDataRequest[requestIndex].isWrite;
		//Buffer hitted.
		if (hash_p2f.findPage(pageID)){
			hitCount ++;
			fullLRU.adjustLRU(pageID);
		}
		//Buffer missed.
		else{
			IOCount ++;
			disk.inputProcess(pageID);
			//EmptyLRU still available.
			if(emptyLRU.getAvailableNodeCount() > 0){
				//Add to LRU link list.
				emptyLRU.setAvailableNodeCountMinusOne();
				LRUElement * emptyNode = emptyLRU.returnTheOneBeforeTrail();
				emptyNode ->pageID =pageID;
				emptyLRU.dropNode(emptyNode);
				fullLRU.insertNodeOnTrail(emptyNode);
				//Add to Hash table.
				int frameID = emptyNode ->frameID;
				hash_p2f.insertBCB(frameID,pageID,isWrite);
			}
			//EmptyLRU does't available.
			else{
				LRUElement * replacing = fullLRU.returnTheOneAfterHead();
				int victimFrameID = replacing ->frameID;
				int victimPageID = replacing ->pageID;
				//Update the Hash Table.
				BCB * victim = hash_p2f.locateNode(victimPageID);
				if(victim ->isWrite == true){
					disk.outputProcess(pageID);
				}
				int frameID = victim ->frameID;
				hash_p2f.dropBCB(victim);
				hash_p2f.insertBCB(frameID,pageID,isWrite);
				delete victim;
				//Update the LRU link list.
				replacing ->pageID = pageID;
				fullLRU.dropNode(replacing);
				fullLRU.insertNodeOnTrail(replacing);
			}
		}
	}
	//write the changed data back to the disk before exit.
	disk.outputProcess(0);
	clock_t endTime = clock();
	cout << "#   Buffer Size: " << BUFFERSIZE  << "\t\tHit Rate: " << setprecision(4) <<(static_cast<float>(hitCount)/TESTCOUNT) * 100 <<"%\t   #" <<endl;
	cout << "#   I/O Count: " << IOCount << "\t\tRunning Time: "<< setprecision(0) << fixed << static_cast<double>(endTime - startTime)/CLOCKS_PER_SEC*1000 << " ms.\t   #" << endl;
	cout << "============================================================" << endl;
	system("pause");
	return 0;
}