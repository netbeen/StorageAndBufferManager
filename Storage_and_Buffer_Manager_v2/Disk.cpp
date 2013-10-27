#include "Disk.h"
#include "Console.h"

using namespace std;

Disk::Disk(){
	init();
}

//
void Disk::init(){
	ofstream diskFileInit("data.dbf");
	char initBuffer[MAXPAGES * PAGESIZE];
	memset(initBuffer,0,sizeof(initBuffer));
	diskFileInit.write(initBuffer,sizeof(initBuffer));
	diskFileInit.close();

	frame = new char[FRAMESIZE];
	
	diskFileInit.open("index.hdd");
	diskFileInit.write(initBuffer,sizeof(initBuffer));
	diskFileInit.close();

	diskFileInit.open("pageTable.hdd");
	diskFileInit.write(initBuffer,sizeof(initBuffer));
	diskFileInit.close();

	input.open("data.dbf",ios::binary);
	index.open("index.hdd",ios::binary);
	pageTable.open("pageTable.hdd",ios::binary);
	output.open("data.dbf",ios::binary);

	cout << "#   (2/5) HDD initialize competed.                         #" << endl;
}


void Disk::inputProcess(const int pageID){
	//Search the index file.
	index.seekg(((rand()%MAXPAGES) * PAGESIZE), ios::beg);
	index.read(frame, FRAMESIZE);

	//Search the page table.
	pageTable.seekg(((rand()%MAXPAGES) * PAGESIZE), ios::beg);
	pageTable.read(frame, FRAMESIZE);

	//Read the file.
	input.seekg((pageID * PAGESIZE), ios::beg);
	input.read(frame, FRAMESIZE);

}

void Disk::outputProcess(const int pageID){
	//Search the index file.
	index.seekg(((rand()%MAXPAGES) * PAGESIZE), ios::beg);
	index.read(frame, FRAMESIZE);

	//Search the page table.
	pageTable.seekg(((rand()%MAXPAGES) * PAGESIZE), ios::beg);
	pageTable.read(frame, FRAMESIZE);

	//Write into the file.
	output.seekp((pageID * PAGESIZE), ios::beg);
	output.write(frame, FRAMESIZE);

}
