/*

ClassLoader for "VM" front end.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

#include <iostream>
#include <fstream>
#include <sstream>
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

		if(classExists()) {

			ifstream ifs(the_class, ios::binary|ios::ate);
	    	ifstream::pos_type pos = ifs.tellg();

	    	vector<BYTE> bytes(pos);

	    	ifs.seekg(0, ios::beg);
	    	ifs.read(&bytes[0], pos);

	    	return bytes;
	    }
	    else {
	    	cout << "\nCannot open file: " << the_class << endl;
	    	cout << "It does not exist or is inaccessible." << endl;
	    	exit(-1);
	    }
	}

	/**
	 * Check that classfile exists.
    */
	bool classExists() {
		ifstream f(the_class);
		return f.good();
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
	 * Get decimal integer from hexadecimal value.
	*/
	 int getDecInt(string hexv) {
		unsigned int udec;
		istringstream iss(hexv);
		iss >> hex >> udec;
		if(udec == 2) udec = 47;
		if(udec == 4) udec = 79;
		if(udec == 6) udec = 111;
		return static_cast<int>(udec);
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
	string lookupMnemonicInstruction(int bytecode) {
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
			USHORT _byte = (USHORT)classContents.at(i+z);
			if(_byte >= 1 && _byte < 11 && _byte != 2) {
				break;	
			}
			stringstream sstream;
			sstream << hex << (USHORT)classContents.at(i+z);
			string s = sstream.str();

			s = stripFs(s);
			classContents.at(i+z) = 0;
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
			USHORT _byte = (USHORT)classContents.at(i+z);
			if(_byte >= 1 && _byte < 11 && _byte != 2) {
				break;	
			}
			stringstream sstream;
			sstream << hex << _byte;
			string s = sstream.str();

			s = stripFs(s);
			classContents.at(i+z) = 0;
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
	 	int y = cf.getCPCOUNT() * 9;

	 	for(int i = n; i < y; ++i) {

	 		cout << (int)classContents.at(i) << endl;

	 		string tag = cf.getTag((int)classContents.at(i));
	 		vector<string> object;

	 		if(tag.compare("Methodref") == 0) {
	 			int byte1 = (int)classContents.at(i+2);
	 			int byte2 = (int)classContents.at(i+4);
	 			classContents.at(i+2) = 0; // Set byte to 0 to prevent re-read of byte.
	 			classContents.at(i+4) = 0;
	 			object.clear();
	 			object = setConstantPoolArray(tag, to_string(byte1), to_string(byte2));
	 			cf.setCPSIZE(5, "Methodref");
	 		}
	 		else if(tag.compare("Class") == 0) {
	 			object.clear();
	 			object = setConstantPoolArray(tag, to_string((int)classContents.at(i+2)), "");
	 			classContents.at(i+2) = 0;
	 			cf.setCPSIZE(3, "Class");
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
	 			cf.setCPSIZE(5, "Integer");
	 		}
	 		else if(tag.compare("String") == 0) {
	 			object.clear();
	 			object = setConstantPoolArray(tag, to_string((int)classContents.at(i+2)), "");
	 			cf.setCPSIZE(3, "String");
	 		}
	 		else if(tag.compare("NameAndType") == 0) {
	 			int byte1 = (int)classContents.at(i+2);
	 			int byte2 = (int)classContents.at(i+4);
	 			object.clear();
	 			object = setConstantPoolArray(tag, to_string(byte1), to_string(byte2));
	 			cf.setCPSIZE(5, "NameAndType");
	 		}
	 		else if(tag.compare("Utf8") == 0) {
	 			int utf8ByteLength = 3;
	 			int size = (int)classContents.at(i+2);

	 			// *********************************************************************
	 			cout << "Declared UTF-8 size = " << size << endl;
	 			// *********************************************************************

	 			classContents.at(i+2) = 0;
	 			vector<string> values = getHexadecimalValues(i+1, size);
	 			string utf8 = "";
	 			for(int z = 0; z < values.size(); ++z) {
	 				int utf8int = getDecInt(values.at(z));
	 				//cout << "utf8int = " << dec << utf8int << endl;
	 				utf8 += getUTF8Char(utf8int);
	 				++utf8ByteLength;
	 			}

	 			// ************************************************************
	 			// cout << "Utf8 string is: " << "\"" << utf8 << "\"" << endl;
	 			// cout << endl;
	 			// ************************************************************

	 			if(utf8.length() > 2) {
	 				cout << "Utf-8 length: " << utf8ByteLength << endl;
	 				object.clear();
	 				object = setConstantPoolArray(tag, utf8, "");
	 				cf.setCPSIZE(utf8ByteLength, "Utf8");
	 			}
	 		}
	 	}
	 }

	 /**
	  * Set access flags for classfile.
	 */
	 void setAccessFlags() {
	 	int cpsize = cf.getCPSIZE();
	 	int accessFlags = classContents.at(cpsize + 10) + classContents.at(cpsize + 11);
	 	cf.setAccessFlags(accessFlags);
	 }

	 /**
	  * Set this class for classfile.
	 */
	 void setThisClass() {
	 	int cpsize = cf.getCPSIZE();
	  	int thisClass = classContents.at(cpsize + 12) + classContents.at(cpsize + 13);
	  	cf.setThisClass(thisClass);
	 }

	 /**
	   * Set super class for classfile.
	 */
	 void setSuperClass() {
	 	int cpsize = cf.getCPSIZE();
	 	int superClass = classContents.at(cpsize + 14) + classContents.at(cpsize + 15);
	 	cf.setSuperClass(superClass);
	 }

	 /**
	  * Set interfaces count.
	 */
	 void setInterfacesCount() {
	 	int cpsize = cf.getCPSIZE();
	 	int interfacesCount = classContents.at(cpsize + 16) + classContents.at(cpsize + 17);
	 	cf.setStartByte(18);
	 	cf.setInterfacesCount(interfacesCount);
	 }

	 /**
	  * Set interfaces to interfaces table.
	 */
	 void pushInterfaces() {
	 	int cpsize = cf.getCPSIZE();
	 	int x = cf.getStartByte();
	 	int interfacesCount = cf.getInterfacesCount();
	 	if(interfacesCount > 0) {
	 		for(int i = 0; i < interfacesCount; ++i) {
	 			int interface = classContents.at(cpsize + x) + classContents.at(cpsize + (x + 1));
	 			cf.pushInterface(interface);
	 			++x;
	 		}
	 		cf.setStartByte(x + 1);
	 	}
	 }

	 /**
	  * Set fields count.
	 */
	 void setFieldsCount() {
	 	int cpsize = cf.getCPSIZE();
	 	int x = cf.getStartByte();
	 	int fieldsCount = classContents.at(cpsize + x) + classContents.at(cpsize + (x + 1));
	 	cf.setStartByte(x + 2);
	 	cf.setFieldsCount(fieldsCount);
	 }

	 /**
	  * Push any fields to fields table.
	 */
	 void pushFields() {
	 	int cpsize = cf.getCPSIZE();
	 	int x = cf.getStartByte();
	 	int fieldsCount = cf.getFieldsCount();
	 	if(fieldsCount > 0) {
	 		for(int i = 0; i < fieldsCount; ++i) {
	 			int field = classContents.at(cpsize + x) + classContents.at(cpsize + (x + 1));
	 			cf.pushField(field);
	 			++x;
	 		}
	 		cf.setStartByte(x + 1);
	 	}
	 }

	 /**
	  * Set methods count.
	 */
	 void setMethodsCount() {
	 	int cpsize = cf.getCPSIZE();
	 	int x = cf.getStartByte();
	 	int methodsCount = classContents.at(cpsize + x) + classContents.at(cpsize + (x + 1));
	 	cf.setStartByte(x + 2);
	 	cf.setMethodsCount(methodsCount);
	 }

	 /**
	  * Push any methods to methods table.
	 */
	 void pushMethods() {
	 	int cpsize = cf.getCPSIZE();
	 	int x = cf.getStartByte();
	 	int methodsCount = cf.getMethodsCount();
	 	/*if(methodsCount > 0) {
	 		for(int i = 0; i < methodsCount; ++i) {
	 			int method = classContents.at(cpsize + x) + classContents.at(cpsize + (x + 1));
	 			cf.pushMethod(method);
	 			++x;
	 		}
	 		cf.setStartByte(x + 1);
	 	}*/
	 }

	 /**
	  * Set attributes count.
	 */
	 void setAttributesCount() {
	 	int cpsize = cf.getCPSIZE();
	 	int x = cf.getStartByte();
	 	int attribsCount = classContents.at(cpsize + x) + classContents.at(cpsize + (x + 1));
	 	cf.setStartByte(x + 2);
	 	cf.setAttributesCount(attribsCount);	 	
	 }

	 /**
	  * Push any attributes to attributes table.
	 */
	 void pushAttributes() {
	 	int cpsize = cf.getCPSIZE();
	 	int x = cf.getStartByte();
	 	/*int attribsCount = cf.getAttributesCount();
	 	if(attribsCount > 0) {
	 		for(int i = 0; i < attribsCount; ++i) {
	 			int attribute = classContents.at(cpsize + x) + classContents.at(cpsize + (x + 1));
	 			cf.pushAttribute(attribute);
	 			++x;
	 		}
	 		cf.setStartByte(x + 20);
	 	}*/
	 }

	 /**
	  * Set bytecodes count. 
	 */
	 void setBytecodesCount() {
	  	int cpsize = cf.getCPSIZE();
	  	int x = cf.getStartByte();
	  	int bytecodesCount = classContents.at(cpsize + x) + classContents.at(cpsize + (x + 1));
	  	cf.setStartByte(x + 20);
	  	cf.setBytecodesCount(bytecodesCount);
	  }

	 /**
	  * Push bytecodes to bytecodes table.
	 */
	 void pushBytecodes() {
	 	int cpsize = cf.getCPSIZE();
	 	int x = cf.getStartByte();
	 	int bytecodesCount = cf.getBytecodesCount();
	 	if(bytecodesCount > 0) {
	 		for(int i = 0; i < bytecodesCount; ++i) {
	 			int bytecode = classContents.at(cpsize + x) + classContents.at(cpsize + (x + 1)); 
	 			cf.pushBytecode(bytecode);
	 			++x;
	 		}
	 	}
	 	cf.setStartByte(x);
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
			setAccessFlags();
			setThisClass();
			setSuperClass();
			setInterfacesCount();
			pushInterfaces();
			setFieldsCount();
			pushFields();
			setMethodsCount();
			pushMethods();
			setAttributesCount();
			pushAttributes();
			setBytecodesCount();
			pushBytecodes();

			// ***********************************************************************
			cout << "CP_COUNT = " << cf.getCPCOUNT() << endl;
			cout << "CP_SIZE = " << cf.getCPSIZE() << endl;

			cout << "Access flags: " << hex << cf.getAccessFlags() << endl;
			cout << "This class: " << cf.getThisClass() << endl;
			cout << "Super class: " << cf.getSuperClass() << endl;
			cout << "Interfaces count: " << cf.getInterfacesCount() << endl;
			cout << "Fields count: " << cf.getFieldsCount() << endl;
			cout << "Methods count: " << cf.getMethodsCount() << endl;
			cout << "Attributes count: " << cf.getAttributesCount() << endl;
			cout << "Bytecodes count: " << cf.getBytecodesCount() << endl;

			cout << "\nBytecodes: " << endl << endl;
			vector<int> bytecodes = cf.pullBytecodes();
			for(int i = 0; i < cf.getBytecodesCount(); ++i) {
				cout << hex << bytecodes.at(i) << endl;
			}
			// ***********************************************************************
		}
		else {
			cout << "Invalid Java classfile. Terminating now..." << endl;
			exit(-1);
		}
	}
};
