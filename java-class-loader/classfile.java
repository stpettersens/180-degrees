//package
/*

The "VM" - a front end to the classloader.
Ported from C++ to Java.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

import java.util.ArrayList;

class ClassFile {

	private long magic;
	private int minor_version;
	private int major_version;
	private int constant_pool_count;
	private ArrayList<ArrayList<String>> constant_pool;
	private ArrayList<Integer> cp_size;
	private int access_flags;
	private int this_class;
	private int super_class;
	private int interfaces_count;
	private ArrayList<String> interfaces;
	private int fields_count;
	private ArrayList<String> fields;
	private int methods_count;
	private ArrayList<String> methods;
	private int attributes_count;
	private ArrayList<String> attributes;
	private String[] tags;

	ClassFile() { // Constructor for ClassFile.
		magic = 0;
		minor_version = 0;
		major_version = 0;
		constant_pool_count = 0;
		cp_size = new ArrayList<Integer>();
		access_flags = 0;
		this_class = 0;
		super_class = 0;
		fields_count = 0;
		attributes_count = 0;

		tags = new String[13];
		tags[0] = "Null";
		tags[1] = "Utf8";
		tags[2] = "Null";
		tags[3] = "Integer";
		tags[4] = "Float";
		tags[5] = "Long";
		tags[6] = "Double";
		tags[7] = "Class";
		tags[8] = "String";
		tags[9] = "Fieldref";
		tags[10]= "Methodref";
		tags[11]= "InterfaceMethodref";
		tags[12]= "NameAndType";
	}
	void setMagicNumber(long magicNum) {
		magic = magicNum;
	}
	long getMagicNumber() {
		return magic;
	}
	boolean checkMagicNumber() {
		boolean isMagic = false;
		// 0xCAFEBABE = 3405691582L
		if(magic == 3405691582L) isMagic = true;
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
	void pushToConstantPool(ArrayList<String> constValPair) {
		constant_pool.add(constValPair); // Possibly make this a String[2] array.
	}
	void setCPSIZE(int tagSize) {
		cp_size.add(tagSize);
	}
	int getCPSIZE() {
		int f_cpsize = 0;
		for(int i = 0; i <= cp_size.size(); ++i) {
			f_cpsize += cp_size.get(i);
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
	void setInterfacesCount(int interfacesCount) {
		interfaces_count = interfacesCount;
	}
	int getInterfacesCount() {
		return interfaces_count;
	}
	void pushInterface(String _interface) {
		interfaces.add(_interface);
	}
	void setFieldsCount(int fieldsCount) {
		fields_count = fieldsCount;
	}
	int getFieldsCount() {
		return fields_count;
	}
	void pushField(String field) {
		fields.add(field);
	}
	void setMethodsCount(int methodsCount) {
		methods_count = methodsCount;
	}
	int getMethodsCount() {
		return methods_count;
	}
	void pushMethod(String method) {
		methods.add(method);
	}
	void setAttributesCount(int attribCount) {
		attributes_count = attribCount;
	}
	int getAttributesCount() {
		return attributes_count;
	}
	void pushAttribute(String attribute) {
		attributes.add(attribute);
	}
	String getTag(int index) {
		String rtag = "Invalid tag index";
		if(index != 0 || index != 2) rtag = tags[index];
		return rtag;
	}
}
