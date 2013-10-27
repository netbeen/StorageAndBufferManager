#include "Disk.h"
#include "Console.h"

using namespace std;

Disk::Disk(){
	init();
}

void Disk::init(){
	ofstream diskFileInit("data.dbf");
	char initBuffer[MAXPAGES * PAGESIZE];
	memset(initBuffer,0,sizeof(initBuffer));
	diskFileInit.write(initBuffer,sizeof(initBuffer));
	diskFileInit.close();

	input.open("data.dbf",ios::binary);
	output.open("data.dbf",ios::binary);
	frame = new char[FRAMESIZE];
	cout << "HDD initialize competed." << endl;
}


void Disk::inputProcess(const int pageID){
	//input.open("data.dbf",ios::binary);
	/*//Search the index file.
	input.seekg(((rand()%MAXPAGES) * PAGESIZE), ios::beg);
	input.read(frame, FRAMESIZE);

	//Search the page table.
	input.seekg(((rand()%MAXPAGES) * PAGESIZE), ios::beg);
	input.read(frame, FRAMESIZE);*/

	input.seekg((pageID * PAGESIZE), ios::beg);
	input.read(frame, FRAMESIZE);
	//input.close();
}

void Disk::outputProcess(const int pageID){
	//output.open("data.dbf",ios::binary);
	/*//Search the index file.
	input.seekg(((rand()%MAXPAGES) * PAGESIZE), ios::beg);
	input.read(frame, FRAMESIZE);

	//Search the page table.
	input.seekg(((rand()%MAXPAGES) * PAGESIZE), ios::beg);
	input.read(frame, FRAMESIZE);*/

	output.seekp((pageID * PAGESIZE), ios::beg);
	output.write(frame, FRAMESIZE);
	//output.close();
}
