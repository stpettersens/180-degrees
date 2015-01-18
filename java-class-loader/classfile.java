//package

/*
ClassFile class for ClassLoader.
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
	private int start_byte;
	private int interfaces_count;
	private ArrayList<Integer> interfaces;
	private int fields_count;
	private ArrayList<Integer> fields;
	private int methods_count;
	private ArrayList<Integer> methods;
	private int attributes_count;
	private ArrayList<Integer> attributes;
	private int bytecodes_count;
	private ArrayList<Integer> bytecodes;
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
		start_byte = 0;
		fields_count = 0;
		attributes_count = 0;
		bytecodes_count = 0;
		bytecodes = new ArrayList<Integer>();

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
	void setCPSIZE(int tagSize, String type) {
		System.out.println(String.format("+ %d (%s)\n", tagSize, type));
		cp_size.add(tagSize);
	}
	int getCPSIZE() {
		int f_cpsize = 0;
		for(int i = 0; i < cp_size.size(); ++i) {
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
	void pushInterface(int _interface) {
		interfaces.add(_interface);
	}
	ArrayList<Integer> pullInterfaces() {
		return interfaces;
	}
	void setFieldsCount(int fieldsCount) {
		fields_count = fieldsCount;
	}
	int getFieldsCount() {
		return fields_count;
	}
	void pushField(int field) {
		fields.add(field);
	}
	ArrayList<Integer> pullFields() {
		return fields;
	}
	void setMethodsCount(int methodsCount) {
		methods_count = methodsCount;
	}
	int getMethodsCount() {
		return methods_count;
	}
	void pushMethod(int method) {
		methods.add(method);
	}
	ArrayList<Integer> pullMethods() {
		return methods;
	}
	void setAttributesCount(int attribsCount) {
		attributes_count = attribsCount;
	}
	int getAttributesCount() {
		return attributes_count;
	}
	void pushAttribute(int attribute) {
		attributes.add(attribute);
	}
	ArrayList<Integer> pullAttributes() {
		return attributes;
	}
	void setBytecodesCount(int bytecodesCount) {
		bytecodes_count = bytecodesCount;
	}
	int getBytecodesCount() {
		return bytecodes_count;
	}
	void pushBytecode(int bytecode) {
		bytecodes.add(bytecode);
	}
	ArrayList<Integer> pullBytecodes() {
		return bytecodes;
	}
	String getTag(int index) {
		String rtag = "Null";
		if(index != 0 || index != 2 || index <= 12 || index > 0) {
			rtag = tags[index];
		}
		return rtag;
	}
}
