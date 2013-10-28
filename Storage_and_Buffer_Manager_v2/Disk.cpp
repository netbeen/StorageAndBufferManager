#include "Disk.h"
#include "Console.h"

using namespace std;

//
Disk::Disk(){
	init();
}

//Initialize the HDD.
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

	diskFileInit.open("log.dbf");
	diskFileInit.close();

	input.open("data.dbf",ios::binary);
	index.open("index.hdd",ios::binary);
	pageTable.open("pageTable.hdd",ios::binary);
	output.open("data.dbf",ios::binary);
	log.open("log.dbf",ios::binary);

	cout << "#   (2/5) HDD initialize competed.                         #" << endl;
}

Disk::~Disk(){
	index.close();
	pageTable.close();
	log.close();
	input.close();
	output.close();
}

//Startup the read process, read 4KB data from "data.dbf"
void Disk::inputProcess(const int pageID){
	//Search the index file.
	searchIndex();

	//Search the page table.
	searchPageTable();	

	//Read the file.
	input.seekg((pageID * PAGESIZE), ios::beg);
	input.read(frame, FRAMESIZE);

}

//Startup the write process, write 4KB data into "data.dbf"
void Disk::outputProcess(const int pageID){
	//Search the index file.
	searchIndex();

	//Search the page table.
	searchPageTable();

	writeLog(pageID);

	//Write into the file.
	output.seekp((pageID * PAGESIZE), ios::beg);
	output.write(frame, FRAMESIZE);

}

//Search the index file. In NTFS, the index file dafualt size is 512B.
void Disk::searchIndex(){
	index.seekg(((rand()%MAXPAGES) * PAGESIZE), ios::beg);
	index.read(frame, NTFSINDEXPAGESIZE);
}

//Search the page table file. In NTFS, the page table file dafualt size is 4KB.
void Disk::searchPageTable(){
	pageTable.seekg(((rand()%MAXPAGES) * PAGESIZE), ios::beg);
	pageTable.read(frame, NTFSPAGETABLESIZE);
}

//Write system log into disk.
void Disk::writeLog(const int pageID){
	log << static_cast<double>(clock())/CLOCKS_PER_SEC*1000 << "ms\t\tWrite page " << pageID <<" into disk.\r\n";
}