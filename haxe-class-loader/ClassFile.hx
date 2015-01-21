/*
ClassFile class for ClassLoader.
Ported from C++ to Haxe.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.
*/

#if neko
import neko.Lib;
#elseif cpp
import cpp.Lib;
#end

class ClassFile {

	var magic: Int;
	var minor_version: Int;
	var major_version: Int;
	var constant_pool_count: Int;
	var constant_pool: Array<Map<String,String>>;
	var cp_size: Array<Int>;
	var access_flags: Int;
	var this_class: Int;
	var super_class: Int;
	var start_byte: Int;
	var interfaces_count: Int;
	var interfaces: Array<Int>;
	var fields_count: Int;
	var fields: Array<Int>;
	var methods_count: Int;
	var methods: Array<Int>;
	var attributes_count: Int;
	var attributes: Array<Int>;
	var bytecodes_count: Int;
	var bytecodes: Array<Int>;
	var tags: Array<String>;

	public function new() { // Constructor for ClassFile.
		magic = 0;
		minor_version = 0;
		major_version = 0;
		constant_pool_count = 0;
		constant_pool = [];
		cp_size = [];
		access_flags = 0;
		this_class = 0;
		super_class = 0;
		start_byte = 0;
		interfaces_count = 0;
		interfaces = [];
		fields_count = 0;
		fields = [];
		methods_count = 0;
		methods = [];
		attributes_count = 0;
		bytecodes_count = 0;
		bytecodes = [];

		tags = [ "Null", "Utf8", "Null", "Integer", "Float", "Long", "Double" ];
		tags[7] = "Class";
		tags[8] = "String";
		tags[9] = "Fieldref";
		tags[10] = "InterfaceMethodref";
		tags[11] = "NameAndType";
	}

	public function setMagicNumber(magicNum: Int): Void {
		magic = magicNum;
	}
	public function getMagicNumber(): Int {
		return magic;
	}
	public function checkMagicNumber(): Bool {
		var isMagic: Bool = false;
		if(magic == 0xCAFEBABE) isMagic = true;
		return isMagic;
	}
	public function setMinorVersion(minorVer: Int): Void {
		minor_version = minorVer;
	}
	public function getMinorVersion(): Int {
		return minor_version;
	}
	public function setMajorVersion(majorVer: Int): Void {
		major_version = majorVer;
	}
	public function getMajorVersion(): Int {
		return major_version;
	}
	public function setConstantPoolCount(cpCount: Int): Void {
		constant_pool_count = cpCount;
	}
	public function getCPCOUNT(): Int {
		return constant_pool_count;
	}
	public function pushToConstantPool(constValPair: Map<String,String>): Void {
		constant_pool.push(constValPair);
	}
	public function setCPSIZE(tagSize: Int, type: String): Void {
		Lib.println("+ " + tagSize + " (" + type + ")\n");
		cp_size.push(tagSize);
	}
	public function getCPSIZE(): Int {
		var f_cpsize: Int = 0;
		for (i in cp_size) {
			f_cpsize += cp_size[i];
		}
		return f_cpsize;
	}
	public function setAccessFlags(accessFlags: Int): Void {
		access_flags = accessFlags;
	}
	public function setThisClass(thisClass: Int): Void {
		this_class = thisClass;
	}
	public function getThisClass(): Int {
		return this_class;
	}
	public function setSuperClass(superClass: Int): Void {
		super_class = superClass;
	}
	public function getSuperClass(): Int {
		return super_class;
	}
	public function setStartByte(start: Int): Void {
		start_byte = start;
	}
	public function getStartByte(): Int {
		return start_byte;
	}
	public function setInterfacesCount(interfacesCount: Int): Void {
		interfaces_count = interfacesCount;
	}
	public function getInterfacesCount(): Int {
		return interfaces_count;
	}
	public function pullInterfaces(): Array<Int> {
		return interfaces;
	}
	public function setFieldsCount(fieldsCount: Int): Void {
		fields_count = fieldsCount;
	}
	public function getFieldsCount(): Int {
		return fields_count;
	}
	public function pushField(field: Int): Void {
		fields.push(field);
	}
	public function pullFields(): Array<Int> {
		return fields;
	}
	public function setMethodsCount(methodsCount: Int): Void {
		methods_count = methodsCount;
	}
	public function getMethodsCount(): Int {
		return methods_count;
	}
	public function pushMethod(method: Int): Void {
		methods.push(method);
	}
	public function pullMethods(): Array<Int> {
		return methods;
	}
	public function setAttributesCount(attribsCount: Int): Void {
		attributes_count = attribsCount;
	}
	public function getAttributesCount(): Int {
		return attributes_count;
	}
	public function pushAttribute(attribute: Int): Void {
		attributes.push(attribute);
	}
	public function pullAttributes(): Array<Int> {
		return attributes;
	}
	public function setBytecodesCount(bytecodesCount: Int): Void {
		bytecodes_count = bytecodesCount;
	}
	public function getBytecodesCount(): Int {
		return bytecodes_count;
	}
	public function pushBytecode(bytecode: Int): Void {
		bytecodes.push(bytecode);
	}
	public function pullBytecodes(): Array<Int> {
		return bytecodes;
	}
	public function getTag(index: Int): String {
		var rtag: String = "Null";
		if(index != 0 || index != 2 || index <= 12 || index > 0) {
			rtag = tags[index];
		}
		return rtag;
	}
 }