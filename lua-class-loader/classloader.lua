-- ClassLoader for "VM" front end.
-- Ported from C++ to Lua.
--
-- Copyright 2015 Sam Saint-Pettersen
--
-- Released under the MIT/X11 License.
-- Please see LICENSE file.

require 'classfile'

ClassLoader = {}
ClassLoader.__index = ClassLoader

function ClassLoader.create()

	local self = setmetatable({}, ClassLoader)

	self.classContents = {}
	self.cf = ClassFile.create()
	self.the_class = ''

	return self
end

--
-- Load a Java classfile and dumpm loaded structure if specified.
--
function ClassLoader:load(class, dump)

	self.the_class = class
	self.classContents = self:readClassBytes()
	self:setMagicNumber()

	if self.cf:checkMagicNumber() then

		-- *****************************************************************************
		local magic = self.cf:getMagicNumber()
		local hmagic = string.format('%02X', magic)
		print(string.format('\nMagic number (hex = %s) (dec: %d)', hmagic, magic))
		-- *****************************************************************************

		self:setMinorVersion()
		self:setMajorVersion()

		-- *************************************************************************
		local minor = self.cf:getMinorVersion()
		local hminor = string.format('%02X', minor)
		print(string.format('\nMinor version = %d (hex: %s)', minor, hminor))

		local major = self.cf:getMajorVersion()
		local hmajor = string.format('%02X', major)
		print(string.format('Major version = %d (hex: %s)\n', major, hmajor))
		-- *************************************************************************
	else
		print("\nInvalid Java classfile. Terminating now...\n")
		os.exit(-1)
	end
end

--
-- Check that a file exists.
--
function ClassLoader:fileExists(file)
	local f = io.open(file, 'r')
	if f ~= nil then
		io.close(f)
		return true
	else
		return false
	end
end

--
-- Read in Java classfile byte-by-byte.
--
function ClassLoader:readClassBytes()
	local bytes = {}
	if self:fileExists(self.the_class) then
		local file = assert(io.open(self.the_class, 'rb'))
		local block = 1
		while true do
			local byte = file:read(block)
			if byte == nil then 
				break
			else
				table.insert(bytes, string.format('%02X', string.byte(byte)))
			end
		end
		file:close()
	else
		print(string.format('\nCannot open file: %s', self.the_class))
		print('It does not exist or is inaccessible.\n')
		os.exit(-1)
	end
	return bytes
end

--
-- Set a section of the loaded Java classfile stored object (cf).
--
function ClassLoader:setClassSection(start, _end, base)
	local fvalue = ''
	local value = {}
	local i = start + 1
	while i <= _end + 1  do
		x = self.classContents[i]
		table.insert(value, x)
		i = i + 1
	end
	local s = ''
	local i = 0
	while i < #value do
		if base == 16 then s = tostring(value[i]) end
		if base == 10 then s = tonumber(tostring(value[i]), 16) end
		fvalue = fvalue .. tostring(s)
		i = i + 1
	end
	fvalue = string.gsub(fvalue, 'nil', '')
	return fvalue
end

--
-- Set and return a constant pool array (table).
--
function ClassLoader:setConstantPoolArray(tag, data1, data2)
	local array = {}
	table.insert(array, tag)
	if data2 == nil then
		table.insert(array, data1)
	else
		table.insert(array, string.format('%s,%s', data1, data2))
	end
	print(string.format('tag: %s', array[0]))
	print(string.format('>>>: %s\n', array[1]))
	return array
end

--
-- Get UTF-8 character for decimal integer value.
--
function ClassLoader:getUTF8Char(dec)
	return string.char(dec)
end

--
-- Look up word mnemonic instruction from bytecode instruction.
--
function ClassLoader:lookupMnemonicInstruction(bytecode)
	return 'instruction' -- TODO
end

--
-- Set magic number for loaded Java classfile.
--
function ClassLoader:setMagicNumber()
	local magic = self:setClassSection(0, 4, 16)
	self.cf:setMagicNumber(tonumber(magic, 16))
end

--
-- Set minor classfile version (e.g. 0).
--
function ClassLoader:setMinorVersion()
	local minor = self:setClassSection(4, 6, 10)
	self.cf:setMinorVersion(tonumber(minor))
end

--
-- Set major classfile version (e.g. 51).
function ClassLoader:setMajorVersion()
	local major = self:setClassSection(6, 8, 10)
	self.cf:setMajorVersion(tonumber(major))
end
