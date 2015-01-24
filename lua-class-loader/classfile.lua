-- ClassFile class for ClassLoader.
-- Ported from C++ to Lua.
--
-- Copyright 2015 Sam Saint-Pettersen
--
-- Released under the MIT/X11 License.
-- Please see LICENSE file.

ClassFile = {}
ClassFile.__index = ClassFile

function ClassFile.create()

	local self = setmetatable({}, ClassFile)

	self.magic = 0
	self.minor_version = 0
	self.major_version = 0
	self.constant_pool_count = 0
	self.constant_pool = {}
	self.cp_size = {}
	self.access_flags = 0
	self.this_class = 0
	self.super_class = 0
	self.start_byte = 0
	self.interfaces_count = 0
	self.interfaces = {}
	self.fields_count = 0
	self.fields = {}
	self.methods_count = 0
	self.methods = {}
	self.attributes_count = 0
	self.attributes = {}
	self.bytecodes_count = 0
	self.bytecodes = {}
	self.tags = { 'Null', 'Utf8', 'Integer', 'Float', 'Long', 'Double' }
	table.insert(self.tags, 'Class')
	table.insert(self.tags, 'String') 
	table.insert(self.tags, 'Fieldref')
	table.insert(self.tags, 'Methodref')
	table.insert(self.tags, 'InterfaceMethodref')
	table.insert(self.tags, 'NameAndType')

	return self
end

function ClassFile:setMagicNumber(magicNum)
	self.magic = magicNum
end

function ClassFile:getMagicNumber()
	return self.magic
end

function ClassFile:checkMagicNumber()
	isMagic = false
	if self.magic == 0xCAFEBABE then 
		isMagic = true
	end
	return isMagic
end

function ClassFile:setMinorVersion(minor)
	self.minor_version = minor
end

function ClassFile:getMinorVersion()
	return self.minor_version
end

function ClassFile:setMajorVersion(major)
	self.major_version = major
end

function ClassFile:getMajorVersion()
	return self.major_version
end

function ClassFile:setCosntantPoolCount(cpCount)
	self.constant_pool_count = cpCount
end

function ClassFile:getCPCOUNT()
	return self.constant_pool_count
end

function ClassFile:pushToConstantPool(constValPair)
	table.insert(self.constant_pool, constValPair)
end

function ClassFile:setCPSIZE(tagSize, _type)
	print('+ ' .. tagSize .. '( ' .. _type .. ')') --!
	table.insert(self.cp_size, tagSize)
end

function ClassFile:getCPSIZE()
	f_cpsize = 0
	for size in self.cpsize do
		f_cpsize = f_cpsize + size
	end
	return f_cpsize
end

function ClassFile:setAccessFlags(accessFlags)
	self.access_flags = accessFlags
end

function ClassFile:getAccessFlags()
	return self.access_flags
end

function ClassFile:setThisClass(thisClass)
	self.this_class = thisClass
end

function ClassFile:getThisClass()
	return self.this_class
end

function ClassFile:setSuperClass(superClass)
	self.super_class = superClass
end

function ClassFile:getSuperClass()
	return self.super_class
end

function ClassFile:setStartByte(start)
	self.start_byte = start
end

function ClassFile:getStartByte()
	return self.start_byte
end

function ClassFile:setInterfacesCount(interfacesCount)
	self.interfaces_count = interfacesCount
end

function ClassFile:getInterfacesCount()
	return self.interfaces_count
end

function ClassFile:pushInterface(interface)
	table.insert(self.interfaces, interface)
end

function ClassFile:pullInterfaces()
	return self.interfaces
end

function ClassFile:setFieldsCount(fieldsCount)
	self.fields_count = fieldsCount
end

function ClassFile:getFieldsCount()
	return self.fields_count
end

function ClassFile:pushField(field)
	table.insert(self.fields, field)
end

function ClassFile:pullFields()
	return self.fields
end

function ClassFile:setMethodsCount(methodsCount)
	self.methods_count = methodsCount
end

function ClassFile:getMethodsCount()
	return self.methods_count
end

function ClassFile:pushMethod(method)
	table.insert(self.methods, method)
end

function ClassFile:pullMethods()
	return self.methods
end

function ClassFile:setAttributesCount(attribsCount)
	self.attributes_count = attribsCount
end

function ClassFile:pushAttibute(attribute)
	table.insert(self.attributes, attribute)
end

function ClassFile:pullAttributes()
	return self.attributes
end

function ClassFile:setBytecodesCount(bytcodesCount)
	self.bytecodes_count = bytcodesCount
end

function ClassFile:getBytecodesCount()
	return self.bytecodes_count
end

function ClassFile:pushBytecode(bytecode)
	table.insert(self.bytecodes, bytecode)
end

function ClassFile:pullBytecodes()
	return self.bytecodes
end

function ClassFile:getTag(index)
	local rtag = 'Null'
	if index ~= 0 or index ~= 2 or index <= 12 or index > 0 then
		rtag = tags[index]
	end
	return rtag
end
