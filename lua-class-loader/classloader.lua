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

		self:setConstantPoolCount()
		self:setConstantPoolTable()

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
	print(string.format('tag: %s', array[1]))
	print(string.format('>>>: %s\n', array[2]))
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
--
function ClassLoader:setMajorVersion()
	local major = self:setClassSection(6, 8, 10)
	self.cf:setMajorVersion(tonumber(major))
end

--
-- Set constant pool count for classfile.
--
function ClassLoader:setConstantPoolCount()
	local constPoolCount = self:setClassSection(8, 10, 10)
	self.cf:setConstantPoolCount(tonumber(constPoolCount))
end

--
-- Get a hexadecimal value for a classfile byte offset.
--
function ClassLoader:getHexadecimalValue(i, length)
	local value = ''
	local z = 2
	local j = 1
	while j < length + 1 do
		print('j is ' .. j)
		print('z is ' .. z)
		print('i is ' .. i)
		print('i + z is ' .. i+z)
		local fuckme = tonumber(tostring(self.classContents[i+z]), 16)
		print('byte is ' .. fuckme)
		--if byte >= 1 and byte < 11 and byte ~= 2 then
			--break
		--end
		s = string.format('%02X', fuckme)
		print(s)
		table.insert(self.classContents, i+z, 0)
		value = value .. s
		z = z + 1
		j = j + 1
	end
	return value
end

--
-- Get a hexadecimal values for a classfile byte offset.
--
function ClassLoader:getHexadecimalValues(i, length)
	local values = {}
	local z = 2
	local j = 0
	while j < length do
		byte = tonumber(self.classContents[i+z], 16)
		if byte >= 1 and byte < 11 and byte ~= 2 then
			break
		end
		s = string.format('%02X', byte)
		table.insert(self.classContents, i+z, 0)
		table.insert(values, s)
		z = z + 1
		j = j + 1
	end
	return values
end

--
-- Set constant pool table for classfile.
--
function ClassLoader:setConstantPoolTable()
	local constPoolTable = {}
	local n = 10
	local x = 1
	local y = self.cf:getCPCOUNT() * 9
	
	local i = n
	while(i < y) do
		print('First i = ' .. i)
		local tag = self.cf:getTag(tonumber(tostring(self.classContents[i]), 16))
		local object = {}

		if tag == 'Methodref' then
			local byte1 = tonumber(self.classContents[i+2], 16)
			local byte2 = tonumber(self.classContents[i+4], 16)
			table.insert(self.classContents, i+2, 0) -- Set byte to 0 to prevent re-read of byte.
			table.insert(self.classContents, i+4, 0)
			table.insert(object, 1, self:setConstantPoolArray(tag, tostring(byte1), tostring(byte2)))
			self.cf:setCPSIZE(5, 'Methodref')

		elseif tag == 'Class' then
			local byte1 = tonumber(self.classContents[i+2], 16)
			table.insert(object, 1, self:setConstantPoolArray(tag, tostring(byte1), nil))
			table.insert(self.classContents, i+2, 0)
			self.cf:setCPSIZE(3, 'Class')

		elseif tag == 'Integer' then
			local integer = tonumber(tostring(self:getHexadecimalValue(i, 4)), 16)

			-- ************************************************************************
			local hinteger = string.format('%02X', integer)
			print(string.format('Integer is: %d (hex: %s)\n\n', integer, hinteger))
			-- ************************************************************************

			--local r = 1
			--while r < 4 do 
				--table.insert(self.classContents, i+r, 0) 
			 	--r = r + 1
			--end

			--table.insert(object, 1, self:setConstantPoolArray(tag, tostring(integer), nil))
			--self.cf:setCPSIZE(5, 'Integer')

		elseif tag == 'String' then
			--local byte1 = tonumber(self.classContents[i+2], 16)
			--table.insert(object, 1, self:setConstantPoolArray(tag, tostring(byte1), nil))
			self.cf:setCPSIZE(3, 'String')

		elseif tag == 'NameAndType' then
			--local byte1 = tonumber(self.classContents[i+2], 16)
			--local byte2 = tonumber(self.classContents[i+2], 16)
			--table.insert(object, 1, self:setConstantPoolArray(tag, tostring(byte1), tostring(byte2)))
			self.cf:setCPSIZE(5, 'NameAndType')

		elseif tag == 'Utf8' then
			--local utf8ByteLength = 3
			--local size = tonumber(self.classContents[i+2], 16)

			-- ***********************************************************
			--print(string.format('Declared UTF-8 size = %d\n', size))
			-- ***********************************************************

			--table.insert(self.classContents, i+2, 0)
			--local values = getHexadecimalValues(i+1, size)
			--local utf8 = ''
			--local z = 1
			--while(z < #values) do
				--local utf8int = tonumber(values[z], 16)
				--utf8 = utf8 .. self:getUTF8Char(utf8int)
				--utf8ByteLength = utf8ByteLength + 1
				--z = z + 1
			--end

			--if #utf8 > 2 then
				--print(string.format('Utf-8 length: %d\n', utf8ByteLength))
				--table.insert(object, 1, self:setConstantPoolArray(tag, utf8, nil))
				--self.cf:setCPSIZE(utf8ByteLength, 'Utf8')
			--end
		end
		i = i + 1
	end
end
