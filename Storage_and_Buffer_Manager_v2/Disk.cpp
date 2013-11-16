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
	
	diskFileInit.open("data.log");
	diskFileInit.close();

	input.open("data.dbf",ios::binary);
	output.open("data.dbf",ios::binary);
	log.open("data.log",ios::binary);

	cout << "#   (2/5) HDD initialize competed.                         #" << endl;
}

//Close the file streams open in my program.
Disk::~Disk(){
	log.close();
	input.close();
	output.close();
}

//Startup the read process, read 4KB data from "data.dbf".
void Disk::inputProcess(const int pageID){

	//Read the file.
	input.seekg((pageID * PAGESIZE), ios::beg);
	input.read(frame, FRAMESIZE);
}

//Startup the write process, write 4KB data into "data.dbf".
void Disk::outputProcess(const int pageID){

	writeLog(pageID);

	//Write into the file.
	output.seekp((pageID * PAGESIZE), ios::beg);
	output.write(frame, FRAMESIZE);
}

//Write system log into "data.log".
void Disk::writeLog(const int pageID){
	log << static_cast<double>(clock())/CLOCKS_PER_SEC*1000 << "ms\t<Write," << pageID <<">\r\n";
}