#ifndef BINARY_FILE_MODEL_H
#define BINARY_FILE_MODEL_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <list>
#include <string>
#include <sstream>

using namespace std;


class BinaryFileHeader
{
 public:
  
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;

  string intToHex(uint32_t);
  string getMagicNumTitle();
  string getVersionNumTitle();
  string getNumRecordsTitle();
  

};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
 public:
  
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
  string getStrLengthTitle();

};

class BinaryFile
{
 public:
  
  ~BinaryFile();
  BinaryFileHeader header;
  list<BinaryFileRecord> records;

  int readFile(string fileName);

};

string BinaryFileHeader::getMagicNumTitle() {
  string returnstr = "Magic: ";
  returnstr += intToHex(magicNumber);
  return returnstr;
  
}

string BinaryFileHeader::getVersionNumTitle() {
  stringstream stream;
  stream << "Version: " << versionNumber;
  return stream.str();

}

string BinaryFileHeader::getNumRecordsTitle() {
  stringstream stream;
  stream << "NumRecords: " << numRecords;
  return stream.str();

}

string BinaryFileHeader::intToHex(uint32_t value) {
  stringstream stream;
  stream << "0x" << setfill('0') << setw(sizeof(uint32_t)*2) << hex << value;
  return stream.str();
}

string BinaryFileRecord::getStrLengthTitle() {
  stringstream stream;
  stream << "strlen: " << unsigned(strLength);
  return stream.str();
  
}

BinaryFile::~BinaryFile(){
  records.clear();
}

int BinaryFile::readFile(string fileName) {
  
  ifstream binInfile(fileName.c_str(), ios::in | ios::binary);
  if(binInfile.is_open()){
    //cout << "File open success." << endl;
  }else{
    //cout << "File did not open." << endl;
  }
  binInfile.read((char *) &header, sizeof(BinaryFileHeader));
  if(header.magicNumber != 0){
    while(!binInfile.eof()) {
      BinaryFileRecord record;
      binInfile.read((char *) &record, sizeof(BinaryFileRecord));
      if(binInfile.gcount() > 0) {
	records.push_back(record);
      }
      else {
	break;
      }
    }
  }else{
    header.magicNumber = 0xEEEEEEEE;
  }
  binInfile.close();
  
  return 0;
  
}



#endif
