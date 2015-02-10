/*

ClassFile class for ClassLoader.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

package main

import "fmt"

type ClassFile struct {
	magic uint32
	minor_version uint16
	major_version uint16
	constant_pool_count uint16
	constant_pool []ConstantValuePair
	cp_size []uint16
	access_flags uint16
	this_class uint16
	super_class uint16
	start_byte byte
	interfaces_count uint16
	interfaces []uint16
	fields_count uint16
	fields []uint16
	methods_count uint16
	methods []uint16
	attributes_count uint16
	attributes []uint16
	bytecodes_count uint16
	bytecodes []uint16
	tags []string
}

type ConstantValuePair struct {
	constVal1 string
	constVal2 string
}

func (cf *ClassFile) new() {
	cf.tags = []string { "Null", "Utf8", "Integer", "Float", "Long", "Double" }
	cf.tags[6]  = "Class"
	cf.tags[7]  = "String"
	cf.tags[8]  = "Fieldref"
	cf.tags[9]  = "Methodref"
	cf.tags[10] = "InterfaceMethodref"
	cf.tags[11] = "NameAndType"
}
func (cf *ClassFile) setMagicNumber(magicNum uint32)  {
	cf.magic = magicNum
}
func (cf *ClassFile) getMagicNumber() (uint32) {
	return cf.magic
}
func (cf *ClassFile) checkMagicNumber() (bool) {
	var isMagic bool = false
	if(cf.magic == 0xCAFEBABE) {
		isMagic = true
	}
	return isMagic
}
func (cf *ClassFile) setMinorVersion(minorVer uint16) {
	cf.minor_version = minorVer
}
func (cf *ClassFile) getMinorVersion() (uint16) {
	return cf.minor_version
}
func (cf *ClassFile) setMajorVersion(majorVer uint16) {
	cf.major_version = majorVer
}
func (cf *ClassFile) getMajorVersion() (uint16) {
	return cf.major_version
}
func (cf *ClassFile) setConstantPoolCount(cpCount uint16) {
	cf.constant_pool_count = cpCount
}
func (cf *ClassFile) getCPCOUNT() (uint16) {
	return cf.constant_pool_count
}
func (cf *ClassFile) pushToConstantPool(constValPair ConstantValuePair) {
	cf.constant_pool = append(cf.constant_pool, constValPair)
}
func (cf *ClassFile) setCPSIZE(tagSize uint16, _type string) {
	fmt.Println(fmt.Sprintf("+ %d (%v)", tagSize, _type))
	cf.cp_size = append(cf.cp_size, tagSize)
}
func (cf *ClassFile) getCPSIZE() (uint16) {
	var f_cpsize uint16 = 0
	for i := 0; i < len(cf.cp_size); i++ {
		f_cpsize += cf.cp_size[i]
	}
	return f_cpsize
}
func (cf *ClassFile) setAccessFlags(accessFlags uint16) {
	cf.access_flags = accessFlags
}
func (cf *ClassFile) getAccessFlags() (uint16) {
	return cf.access_flags
}
func (cf *ClassFile) setThisClass(thisClass uint16) {
	cf.this_class = thisClass
}
func (cf *ClassFile) getThisClass() (uint16) {
	return cf.this_class
}
func (cf *ClassFile) setSuperClass(superClass uint16) {
	cf.super_class = superClass
}
func (cf *ClassFile) getSuperClass() (uint16) {
	return cf.super_class
}
func (cf *ClassFile) setStartByte(start byte) {
	cf.start_byte = start
}
func (cf *ClassFile) getStartByte() (byte) {
	return cf.start_byte
}
func (cf *ClassFile) setInterfacesCount(interfacesCount uint16) {
	cf.interfaces_count = interfacesCount
}
func (cf *ClassFile) getInterfacesCount() (uint16) {
	return cf.interfaces_count
}
func (cf *ClassFile) pushInterface(_interface uint16) {
	cf.interfaces = append(cf.interfaces, _interface)
}
func (cf *ClassFile) pullInterfaces() ([]uint16) {
	return cf.interfaces
}
func (cf *ClassFile) setFieldsCount(fieldsCount uint16) {
	cf.fields_count = fieldsCount
}
func (cf *ClassFile) getFieldsCount() (uint16) {
	return cf.fields_count
}
func (cf *ClassFile) pushField(field uint16) {
	cf.fields = append(cf.fields, field)
}
func (cf *ClassFile) pullFields() ([]uint16) {
	return cf.fields
}
func (cf *ClassFile) setMethodsCount(methodsCount uint16) {
	cf.methods_count = methodsCount
}
func (cf *ClassFile) getMethodsCount() (uint16) {
	return cf.methods_count
}
func (cf *ClassFile) pushMethod(method uint16) {
	cf.methods = append(cf.methods, method)
}
func (cf *ClassFile) pullMethods() ([]uint16) {
	return cf.methods
}
func (cf *ClassFile) setAttributesCount(attribsCount uint16) {
	cf.attributes_count = attribsCount
}
func (cf *ClassFile) getAttributesCount() (uint16) {
	return cf.attributes_count
}
func (cf *ClassFile) pushAttribute(attribute uint16) {
	cf.attributes = append(cf.attributes, attribute)
}
func (cf *ClassFile) pullAttributes() ([]uint16) {
	return cf.attributes
}
func (cf *ClassFile) setBytecodesCount(bytecodesCount uint16) {
	cf.bytecodes_count = bytecodesCount
}
func (cf *ClassFile) getBytecodesCount() (uint16) {
	return cf.bytecodes_count
}
func (cf *ClassFile) pushBytecode(bytecode uint16) {
	cf.bytecodes = append(cf.bytecodes, bytecode)
}
func (cf *ClassFile) pullBytecodes() ([]uint16) {
	return cf.bytecodes
}
func (cf *ClassFile) getTag(index uint16) (string) {
	var rtag string = "Null"
	if(index != 0 || index != 2 || index <= 12 || index > 0) {
		rtag = cf.tags[index]
	}
	return rtag
}
