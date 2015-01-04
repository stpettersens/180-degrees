/*

ClassLoader for "VM" front end.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include "boost/algorithm/string/replace.hpp"
#include "classfile.h"

using namespace std;

typedef char BYTE;

class ClassLoader {

	vector<BYTE> classContents;
	ClassFile cf;
	string the_class;

	vector<BYTE> readClassBytes() {
		ifstream ifs(the_class, ios::binary|ios::ate);
    	ifstream::pos_type pos = ifs.tellg();

    	vector<BYTE> bytes(pos);

    	ifs.seekg(0, ios::beg);
    	ifs.read(&bytes[0], pos);

    	return bytes;
	}

	/**
	 * Set a section of the loaded Java classfile stored object (cf).
	*/
	string setClassSection(int start, int end, int base, bool magic) {
		string fvalue = "";
		vector<unsigned short> value;
		for (int i = start; i < end; ++i)
		{
			unsigned short x = (unsigned short) classContents.at(i);
			value.push_back(x);
		}
		for(int i = 0; i < value.size(); ++i) {
			stringstream sstream;
			if(base == 16) sstream << hex << value.at(i);
			if(base == 10) sstream << dec << value.at(i);
			string s = sstream.str();
			if(base == 16 && magic) {
				// Strip out the 2 leading 'F's in 0xFFCAFEBABE
				// to become 0xCAFEBABE. Hackish, but it works.
				for(int j = 0; j < 2; ++j) {
					boost::replace_first(s, "f", "");
				}
			}
			fvalue += s;
		}
		return fvalue;
	}

	/*
	 * Set and return a constant pool array (vector).
	*/
	vector<string> setConstantPoolArray(string tag, string data1, string data2) {
	 	vector<string> array;
	 	if(data2 == "") {
	 		array.push_back(tag);
	 		array.push_back(data1);
	 	}
	 	else {
	 		array.push_back(tag);
	 		array.push_back(data1 + "," + data2);
	 	}
	 	cout << "tag: " << array.at(0) << endl;
	 	cout << "dt1: " << array.at(1) << endl;
	 	cout << "dt2: " << array.at(2) << endl;
	 	return array;
	}

	/**
	 * Get UTF-8 character for decimal integer value.
	*/
	char getUTF8Char(int dec) {
		return (char) dec;
	}

	/**
	 * Look up word mnemonic instruction from bytecode instruction.
	*/
	string lookupMnemonicInstruction(auto bytecode) {
		return "instruction"; // TODO
	}

	/**
	  * Set magic number for loaded Java classfile.
	*/
	void setMagicNumber() {
		string magic = setClassSection(0, 4, 16, true);
		cf.setMagicNumber(magic);
	}

	/**
	  * Set minor classfile version (e.g. 0).
	*/
	void setMinorVersion() {
		string majorVer = setClassSection(4, 6, 10, false);
		cf.setMinorVersion(stoi(majorVer));
	}

	/**
	  * Set major classfile version (e.g. 51).
	*/
	void setMajorVersion() {
		string minorVer = setClassSection(6, 8, 10, false);
		cf.setMajorVersion(stoi(minorVer));
	}

	/**
	  * Set constant pool count for classfile.
	*/
	void setConstantPoolCount() {
		string constPoolCount = setClassSection(8, 10, 10, false);
		cf.setConstantPoolCount(stoi(constPoolCount));
	}

	/**
	  * Set constant pool size for classfile.
	*/
	 void setCPSIZE(int tagSize) {
	 	cf.setCPSIZE(tagSize);
	 }

	/**
	  * Set contant pool table for classfile.
	*/
	 void setConstantPoolTable() {
	 	vector<string> constPoolTable;
	 	int n = 10;
	 	int x = 1;
	 	int y = 14;

	 	for(int i = n; i < y; ++i) {

	 		string tag = cf.getTag((int) classContents.at(i));
	 		cout << tag << endl;
	 		vector<string> object;
	 		if(strcmp(tag.c_str(), "Methodref") == 0) {
	 			cout << (int) classContents.at(i+2) << endl;
	 			cout << (int) classContents.at(i+4) << endl;
	 			classContents.at(i+2) = 0; // Set byte to 0 to prevent re-read of byte
	 			classContents.at(i+4) = 0;
	 			//object = setConstantPoolArray(tag, byte1, byte2);
	 			setCPSIZE(5);
	 		}
	 		/*else if(strcmp(tag.c_str(), "Class") == 0) {

	 		}*/
	 	}
	 }

public:

	/**
	  * Load a Java classfile and dump loaded structure if specified.
	*/
	void load(string claSS, bool dump) {
		the_class = claSS;
		classContents = readClassBytes();
		setMagicNumber();
		cout << cf.getMagicNumber() << endl; // !
		if(cf.checkMagicNumber()) {
			cout << "Classfile OK..." << endl;
			setMinorVersion();
			setMajorVersion();
			setConstantPoolCount();
			setConstantPoolTable();
		}
		else {
			cout << "Invalid Java classfile. Terminating now..." << endl;
			exit(-1);
		}
	}
};
