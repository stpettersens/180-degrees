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
typedef unsigned short USHORT;

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
	  * Strip leading 2 'F's off a hexdecimal value.
	*/
	string stripFs(string hex) {
		for(int i = 0; i < 2; ++i) {
			boost::replace_first(hex, "f", "");
		}
		return hex;
	}

	/**
	 * Set a section of the loaded Java classfile stored object (cf).
	*/
	string setClassSection(int start, int end, int base, bool magic) {
		string fvalue = "";
		vector<USHORT> value;
		for (int i = start; i < end; ++i)
		{
			USHORT x = (USHORT) classContents.at(i);
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
				s = stripFs(s);
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
	 	cout << ">>>: " << array.at(1) << endl;
	 	cout << endl;
	 	return array;
	}

	/**
	 * Get UTF-8 character for decimal integer value.
	*/
	char getUTF8Char(int dec) {
		return (char)dec;
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
		unsigned long magic = 0;
		string smagic = setClassSection(0, 4, 16, true);
		istringstream iss(smagic);
		iss >> hex >> magic;
		cf.setMagicNumber(magic);
	}

	/**
	  * Set minor classfile version (e.g. 0).
	*/
	void setMinorVersion() {
		string minorVer = setClassSection(4, 6, 10, false);
		cf.setMinorVersion(stoi(minorVer));
	}

	/**
	  * Set major classfile version (e.g. 51).
	*/
	void setMajorVersion() {
		string majorVer = setClassSection(6, 8, 10, false);
		cf.setMajorVersion(stoi(majorVer));
	}

	/**
	  * Set constant pool count for classfile.
	*/
	void setConstantPoolCount() {
		string constPoolCount = setClassSection(8, 10, 10, false);
		cf.setConstantPoolCount(stoi(constPoolCount));
	}

	/**
	  * Get a hexadecimal value for a classfile byte offset.
	*/
	string getHexadecimalValue(int i, int length) {
		string value = "";
		int z = 2;
		for(int j = 0; j < length; ++j) {
			if((USHORT)classContents[i+z] == 1 || (USHORT)classContents[i+z] == 3 || (USHORT)classContents[i+z] == 4 ||
			(USHORT)classContents[i+z] == 5 || (USHORT)classContents[i+z] == 6 || (USHORT)classContents[i+z] == 7 ||
			(USHORT)classContents[i+z] == 8 || (USHORT)classContents[i+z] == 9 || (USHORT)classContents[i+z] == 10) {
				break;	
			}
			stringstream sstream;
			sstream << hex << (USHORT)classContents.at(i+z);
			string s = sstream.str();

			s = stripFs(s);
			value += s;
			++z;
		}
		return value;
	}

	/**
	  * Get hexdecimal values for a classfile byte offset.
	*/
	vector<string> getHexadecimalValues(int i, int length) {
		vector<string> values;
		int z = 2;
		for(int j = 0; j < length; ++j) {
			if((USHORT)classContents[i+z] == 1 || (USHORT)classContents[i+z] == 3 || (USHORT)classContents[i+z] == 4 ||
			(USHORT)classContents[i+z] == 5 || (USHORT)classContents[i+z] == 6 || (USHORT)classContents[i+z] == 7 ||
			(USHORT)classContents[i+z] == 8 || (USHORT)classContents[i+z] == 9 || (USHORT)classContents[i+z] == 10) {
				break;	
			}
			stringstream sstream;
			sstream << hex << (USHORT)classContents.at(i+z);
			string s = sstream.str();

			s = stripFs(s);
			values.push_back(s);
			++z;
		}
		return values;
	}

	/**
	  * Set contant pool table for classfile.
	*/
	 void setConstantPoolTable() {
	 	vector<string> constPoolTable;
	 	int n = 10;
	 	int x = 1;
	 	int y = 35;

	 	for(int i = n; i < y; ++i) {

	 		string tag = cf.getTag((int)classContents.at(i));
	 		vector<string> object;

	 		if(strcmp(tag.c_str(), "Methodref") == 0) {
	 			int byte1 = (int)classContents.at(i+2);
	 			int byte2 = (int)classContents.at(i+4);
	 			classContents.at(i+2) = 0; // Set byte to 0 to prevent re-read of byte.
	 			classContents.at(i+4) = 0;
	 			object.clear();
	 			object = setConstantPoolArray(tag, to_string(byte1), to_string(byte2));
	 			cf.setCPSIZE(5);
	 		}
	 		else if(strcmp(tag.c_str(), "Class") == 0) {
	 			object.clear();
	 			object = setConstantPoolArray(tag, to_string((int)classContents.at(i+2)), "");
	 			classContents.at(i+2) = 0;
	 			cf.setCPSIZE(3);
	 		}
	 		else if(strcmp(tag.c_str(), "Integer") == 0) {
	 			int integer = stoi(getHexadecimalValue(i, 4), 0, 16);

	 			// *************************************************************
	 			cout << "Integer is: " << dec << integer << 
	 			" (hex: " << hex << integer << ")" << endl << endl;
	 			// *************************************************************

	 			for(int r = 1; r <= 4; ++r) {
	 				classContents.at(i+r) = 0;
	 			}
	 			
	 			object.clear();
	 			object = setConstantPoolArray(tag, to_string(integer), "");
	 			cf.setCPSIZE(5);
	 		}
	 		else if(strcmp(tag.c_str(), "String") == 0) {
	 			object.clear();
	 			object = setConstantPoolArray(tag, to_string((int)classContents.at(i+2)), "");
	 			cf.setCPSIZE(3);
	 		}
	 		else if(strcmp(tag.c_str(), "NameAndType") == 0) {
	 			int byte1 = (int)classContents.at(i+2);
	 			int byte2 = (int)classContents.at(i+4);
	 			object.clear();
	 			object = setConstantPoolArray(tag, to_string(byte1), to_string(byte2));
	 			cf.setCPSIZE(5);
	 		}
	 		else if(strcmp(tag.c_str(), "Utf8") == 0) {
	 			int utf8ByteLength = 2;
	 			int size = (int)classContents.at(i+2);
	 			classContents.at(i+2) = 0;
	 			vector<string> values = getHexadecimalValues(i+1, size);
	 			string utf8 = "";
	 			for(int z = 0; z < values.size(); ++z) {
	 				utf8 += getUTF8Char(stoi(values.at(z), 0, 16));
	 				++utf8ByteLength;
	 				//++i;
	 			}

	 			// *********************************************************
	 			cout << "Utf8 string is: " << "\"" << utf8 << "\"" << endl;
	 			cout << endl;
	 			// *********************************************************

	 			if(utf8.length() > 2) {
	 				object.clear();
	 				object = setConstantPoolArray(tag, utf8, "");
	 				cf.setCPSIZE(utf8ByteLength);
	 			}
	 		}
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
		
		// ************************************************************
		unsigned long magic = cf.getMagicNumber();
		cout << "\nMagic number (hex) = " << hex << magic << " (dec: " 
		<< dec << magic << ")" << endl;
		// ************************************************************
		
		if(cf.checkMagicNumber()) {
			cout << endl;
			setMinorVersion();
			setMajorVersion();

			// ********************************************************
			int minorVer = cf.getMinorVersion();
			cout << "Minor version = " << dec << minorVer
			<< " (hex: " << hex << minorVer << ")" << endl;

			int majorVer = cf.getMajorVersion();
			cout << "Major version = " << dec << majorVer
			<< " (hex: " << hex << majorVer << ")" << endl << endl;
			// ********************************************************

			setConstantPoolCount();
			setConstantPoolTable();
		}
		else {
			cout << "Invalid Java classfile. Terminating now..." << endl;
			exit(-1);
		}
	}
};
