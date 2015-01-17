/*
ClassFile class for ClassLoader.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.
*/

#include <string>
#include <vector>

using namespace std;

class ClassFile {

	unsigned long magic;
	int minor_version;
	int major_version;
	int constant_pool_count;
	vector<vector<string>> constant_pool;
	vector<int> cp_size;
	int access_flags;
	int this_class;
	int super_class;
	int start_byte;
	int interfaces_count;
	vector<int> interfaces;
	int fields_count;
	vector<int> fields;
	int methods_count;
	vector<int> methods;
	int attributes_count;
	vector<int> attributes;
	int bytecodes_count;
	vector<int> bytecodes;
	vector<string> tags;

public:

	ClassFile() { // Constructor for ClassFile.
		magic = 0;
		minor_version = 0;
		major_version = 0;
		constant_pool_count = 0;
		access_flags = 0;
		this_class = 0;
		super_class = 0;
		start_byte = 0;
		interfaces_count = 0;
		fields_count = 0;
		methods_count = 0;
		attributes_count = 0;
		bytecodes_count = 0;

		tags = { "Null", "Utf8", "Null", "Integer", "Float", "Long", "Double", \
		"Class", "String", "Fieldref", "Methodref", "InterfaceMethodref", "NameAndType" };
	}
	void setMagicNumber(unsigned long magicNum) {
		magic = magicNum;
	}
	unsigned long getMagicNumber() {
		return magic;
	}
	bool checkMagicNumber() {
		bool isMagic = false;
		if(magic == 0xCAFEBABE) isMagic = true;
		return isMagic;
	}
	void setMinorVersion(int minorVer) {
		minor_version = minorVer;
	}
	int getMinorVersion() {
		return minor_version;
	}
	void setMajorVersion(int majorVer) {
		major_version = majorVer;
	}
	int getMajorVersion() {
		return major_version;
	}
	void setConstantPoolCount(int cpCount) {
		constant_pool_count = cpCount;
	}
	int getCPCOUNT() {
		return constant_pool_count;
	}
	void pushToConstantPool(vector<string> constValPair) {
		constant_pool.push_back(constValPair); // Possibly make this a String[2] array.
	}
	void setCPSIZE(int tagSize, string type) {
		cout << "+ " << dec << tagSize << " (" << type << ")" << endl << endl;
		cp_size.push_back(tagSize);
	}
	int getCPSIZE() {
		int f_cpsize = 0;
		for(int i = 0; i < cp_size.size(); ++i) {
			f_cpsize += cp_size.at(i);
		}
		return f_cpsize;
	}
	void setAccessFlags(int accessFlags) {
		access_flags = accessFlags;
	}
	int getAccessFlags() {
		return access_flags;
	}
	void setThisClass(int thisClass) {
		this_class = thisClass;
	}
	int getThisClass() {
		return this_class;
	}
	void setSuperClass(int superClass) {
		super_class = superClass;
	}
	int getSuperClass() {
		return super_class;
	}
	void setStartByte(int start) {
		start_byte = start;
	}
	int getStartByte() {
		return start_byte;
	}
	void setInterfacesCount(int interfacesCount) {
		interfaces_count = interfacesCount;
	}
	int getInterfacesCount() {
		return interfaces_count;
	}
	void pushInterface(int interface) {
		interfaces.push_back(interface);
	}
	vector<int> pullInterfaces() {
		return interfaces;
	}
	void setFieldsCount(int fieldsCount) {
		fields_count = fieldsCount;
	}
	int getFieldsCount() {
		return fields_count;
	}
	void pushField(int field) {
		fields.push_back(field);
	}
	vector<int> pullFields() {
		return fields;
	}
	void setMethodsCount(int methodsCount) {
		methods_count = methodsCount;
	}
	int getMethodsCount() {
		return methods_count;
	}
	void pushMethod(int method) {
		methods.push_back(method);
	}
	vector<int> pullMethods() {
		return methods;
	}
	void setAttributesCount(int attribsCount) {
		attributes_count = attribsCount;
	}
	int getAttributesCount() {
		return attributes_count;
	}
	void pushAttribute(int attribute) {
		attributes.push_back(attribute);
	}
	vector<int> pullAttributes() {
		return attributes;
	}
	void setBytecodesCount(int bytecodesCount) {
		bytecodes_count = bytecodesCount;
	}
	int getBytecodesCount() {
		return bytecodes_count;
	}
	void pushBytecode(int bytecode) {
		bytecodes.push_back(bytecode);
	}
	vector<int> pullBytecodes() {
		return bytecodes;
	}
	string getTag(int index) {
		string rtag = "Null";
		if(index != 0 || index != 2 || index <= 12 || index > 0) { 
			rtag = tags[index];
		}
		return rtag;
	}
};
