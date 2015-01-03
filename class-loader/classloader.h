/*

ClassLoader for "VM" front end.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string/replace.hpp>
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
	string setClassSection(int start, int end, bool magic) {
		string fvalue = "";
		vector<unsigned short> value;
		for (int i = start; i < end; ++i)
		{
			unsigned short x = (unsigned short) classContents.at(i);
			cout << hex << x << endl;
			cout << dec << x << endl;
			value.push_back(x);
		}
		cout << value.size() << endl;
		for(int i = 0; i < value.size(); ++i) {
			stringstream sstream;
			sstream << hex << value.at(i);
			string s = sstream.str();
			cout << s << endl;
			if(magic) boost::replace_all(s, "f", "");
		}
		cout << fvalue << endl;
		return fvalue;
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

	/**
	  * Set magic number for loaded Java classfile.
	*/
	void setMagicNumber() {
		string magic = setClassSection(0, 4, true);
		//cf.setMagicNumber(stoi(magic)); //stoi(magic));
	}

	/**
	  * Check that set magic number is 0xCAFEBABE.
	  * Return true or display error message and exit.
	*/
	bool checkMagicNumber() {
		bool isValid = false;
		if(cf.checkMagicNumber()) isValid = true;
		return isValid;
	}

public:

	/*
	 * Load a Java classfile and dump loaded structure if specified.
	*/
	void load(string claSS, bool dump) {
		the_class = claSS;
		classContents = readClassBytes();
		setMagicNumber();
	}

	int getClassByte() {
		return (unsigned short) classContents.at(7);
	}

	/**
	  * Get the set magic number for loaded Java classfile.
	*/
	long getMagicNumber() {
		return cf.getMagicNumber();
	}
};
