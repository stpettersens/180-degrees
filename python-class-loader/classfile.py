#!/usr/bin/env python
"""
ClassFile class for ClassLoader.
Ported from C++ to Python.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.
"""

class ClassFile:

	magic = 0
	minor_version = 0
	major_version = 0
	constant_pool_count = 0
	constant_pool = []
	cp_size = []
	access_flags = 0
	this_class = 0
	super_class = 0
	start_byte = 0
	interfaces_count = 0
	interfaces = []
	fields_count = 0
	fields = []
	methods_count = 0
	methods = []
	attributes_count = 0
	attributes = []
	bytecodes_count = 0
	bytecodes = []
	tags = []

	def __init__(self):
		tags = [ 'Null', 'Utf8', 'Null', 'Integer', 'Float', 'Long', 'Double' ]
		tags.append('Class')
		tags.append('String')
		tags.append('Fieldref')
		tags.append('Methodref')
		tags.append('InterfaceMethodref')
		tags.append('NameAndType')

	def setMagicNumber(self, magicNum):
		self.magic = magicNum

	def getMagicNumber(self):
		return self.magic

	def checkMagicNumber(self):
		isMagic = False
		if self.magic == 0xCAFEBABE: isMagic = True
		return isMagic

	def setMinorVersion(self, minorVer):
		self.minor_version = minorVer

	def getMinorVersion(self):
		return self.minor_version

	def setMajorVersion(self, majorVer):
		self.major_version = majorVer

	def setConstantPoolCount(self, cpCount):
		self.constant_pool_count = cpCount

	def getCPCOUNT(self):
		return self.constant_pool_count

	def pushToConstantPool(self, constValPair):
		self.constant_pool.append(constValPair)

	def setCPSIZE(self, tagSize, _type):
		print('+ {0} ({1})'.format(tagSize, _type))
		self.cp_size.append(tagSize)

	def getCPSIZE(self):
		f_cpsize = 0
		for size in self.cp_size:
			f_cpsize += size
		return f_cpsize

	def setAccessFlags(self, accessFlags):
		self.access_flags = accessFlags

	def getAccessFlags(self):
		return self.access_flags

	def setThisClass(self, thisClass):
		self.this_class = thisClass

	def getThisClass(self):
		return self.this_class

	def setSuperClass(self, superClass):
		self.super_class = superClass

	def getSuperClass(self):
		return self.super_class

	def setStartByte(self, start):
		self.start_byte = start

	def getStartByte(self):
		return self.start_byte

	def setInterfacesCount(self, interfacesCount):
		self.interfaces_count = interfacesCount

	def getInterfacesCount(self):
		return self.interfaces_count

	def pushInterface(self, interface):
		self.interfaces.append(interface)

	def pullInterfaces(self):
		return self.interfaces

	def setFieldsCount(self, fieldsCount):
		self.fields_count = fieldsCount

	def getFieldsCount(self):
		return self.fields_count

	def pushField(self, field):
		self.fields.append(field)

	def pullFields(self):
		return self.fields

	def setMethodsCount(self, methodsCount):
		self.methods_count = methodsCount

	def getMethodsCount(self):
		return self.methods_count

	def pushMethod(self, method):
		self.methods.append(method)

	def pullMethods(self):
		return self.methods

	def setAttributesCount(self, attribsCount):
		self.attributes_count = attribsCount

	def getAttributesCount(self):
		return self.attributes_count

	def pushAttribute(self, attribute):
		self.attributes.append(attribute)

	def pullAttributes(self):
		return self.attributes

	def setBytecodesCount(self, bytecodesCount):
		self.bytecodes_count = bytecodesCount

	def getBytecodesCount(self):
		return self.bytecodes_count

	def pushBytecode(self, bytecode):
		self.bytecodes.append(bytecode)

	def pullBytecodes(self):
		return self.bytecodes

	def getTag(self, index):
		rtag = 'Null'
		if index != 0 or index != 2 or index <= 12 or index > 0:
			rtag = self.tags[index]
		return rtag
