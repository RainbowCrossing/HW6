#ifndef BINARY_FILE_MODEL_H
#define BINARY_FILE_MODEL_H

/*
 * Tyler Waller tmw160530@utdallas.edu
 * 3377.501
 * Header file to use with cdk program to read binary file.
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <list>
#include <string>
#include <sstream>

using namespace std;

// Creating classes here to generate usage for functions
// to help read the binary file.
// Functions created to gather the info from the binary
// file to be printed appropriately.
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
/*
 * Records in the file have a fixed length buffer
 * that will hold a C-Style string. This is the
 * size of the fixed length buffer.
 */
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
// These first 3 functions are used to gather the titles
// and information for the first rows of the program.
// Getting the magic number by converting to hex for 
// legible purposes of our magic number.
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
// Function to conver to hex.
string BinaryFileHeader::intToHex(uint32_t value) {
  stringstream stream;
  stream << "0x" << setfill('0') << setw(sizeof(uint32_t)*2) << hex << value;
  return stream.str();
}
// Function for string length for first column.
string BinaryFileRecord::getStrLengthTitle() {
  stringstream stream;
  stream << "strlen: " << unsigned(strLength);
  return stream.str();
  
}
// Destructor.
BinaryFile::~BinaryFile(){
  records.clear();
}
// Looping function to read through and open the bin file
// and appropriately grab the info needed to be placed 
// correctly in our rows and columns.
int BinaryFile::readFile(string fileName) {
  
  ifstream binInfile(fileName.c_str(), ios::in | ios::binary);
  if(binInfile.is_open()){
    //cout << "File open success." << endl;
  }else{
    //cout << "File did not open." << endl;
  }
  binInfile.read((char *) &header, sizeof(BinaryFileHeader));
  // Reading size of to give back the stringlength.
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
  }
  // Should never hit here.
  else{
    header.magicNumber = 0xEEEEEEEE;
  }
  // Closing file.
  binInfile.close();
  
  return 0;
  
}

#endif
