/*
ClassFile class for ClassLoader.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.
*/
#include <string>
#include <vector>
using std::string;
using std::vector;

class ClassFile {

	long magic;
	int minor_version;
	int major_version;
	int constant_pool_count;
	vector<string> constant_pool;
	int cp_size;
	int access_flags;
	int this_class;
	int super_class;
	int interfaces_count;
	vector<string> interfaces;
	int fields_count;
	vector<string> fields;
	int methods_count;
	vector<string> methods;
	int attributes_count;
	vector<string> attributes;
	vector<string> tags;

public:

	ClassFile() { // Constructor for ClassFile.
		magic = 0;
		minor_version = 0;
		major_version = 0;
		constant_pool_count = 0;
		//constant_pool();
		cp_size = 0;
		access_flags = 0;
		this_class = 0;
		super_class = 0;
		interfaces_count = 0;
		//interfaces();
		fields_count = 0;
		//fields();
		methods_count = 0;
		//methods();
		attributes_count = 0;
		//attributes();
		tags = { "", "Utf8", "", "Integer", "Float", "Long", "Double", "Class", "String", "Fieldref", \
		"Methodref", "InterfaceMethodref", "NameAndType" };
	}
	void setMagicNumber(long magicNum) {
		magic = magicNum;
	}
	long getMagicNumber() {
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
	void setMajorVersion(int majorVer) {
		major_version = majorVer;
	}
	void setConstantPoolCount(int cpCount) {
		constant_pool_count = cpCount;
	}
	int getCPCOUNT() {
		return constant_pool_count;
	}
	void pushToConstantPool(string constValPair) {
		constant_pool.push_back(constValPair); // Possibly make this a String[2] array.
	}
	void setCPSIZE(int cpSize) {
		cp_size = cpSize;
	}
	int getCPSIZE() {
		return cp_size;
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
	void setInterfacesCount(int interfacesCount) {
		interfaces_count = interfacesCount;
	}
	int getInterfacesCount() {
		return interfaces_count;
	}
	void pushInterface(string interface) {
		interfaces.push_back(interface);
	}
	void setFieldsCount(int fieldsCount) {
		fields_count = fieldsCount;
	}
	int getFieldsCount() {
		return fields_count;
	}
	void pushField(string field) {
		fields.push_back(field);
	}
	void setMethodsCount(int methodsCount) {
		methods_count = methodsCount;
	}
	int getMethodsCount() {
		return methods_count;
	}
	void pushMethod(string method) {
		methods.push_back(method);
	}
	void setAttributesCount(int attribCount) {
		attributes_count = attribCount;
	}
	int getAttributesCount() {
		return attributes_count;
	}
	void pushAttribute(string attribute) {
		attributes.push_back(attribute);
	}
	string getTag(int index) {
		string rtag = "Invalid tag index";
		if(index != 0 || index != 2) rtag = tags[index];
		return rtag;
	}
};
