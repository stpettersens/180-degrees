/*

ClassLoader for "VM" front end.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

#include <fstream>
#include <string>
#include <vector>
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

	/*
	 * Set a section of the loaded Java classfile stored object (cf).
	*/
	string setClassSection(int start, int end, int base) {
		string value = "";
		for (int i = start; i < end; ++i)
		{
			value += classContents.at(i);
		}
		return value;
	}

	/*
	 * Set and return a constant pool array (vector).
	*/
	vector<string> setConstPoolArray(string tag, string data1, string data2) {
	 	vector<string> array;
	 	if(data2 == "") {
	 		array.push_back(tag);
	 		array.push_back(data1);
	 	}
	 	else {
	 		array.push_back(tag);
	 		array.push_back(data1 + "," + data2);
	 	}
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

public:

	/*
	 * Load a Java classfile and dump loaded structure if specified.
	*/
	void load(string claSS, bool dump) {
		the_class = claSS;
		classContents = readClassBytes();
	}

};
