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
end

function ClassLoader:readClassBytes()
	local bytes = {}
	local file = assert(io.open(self.the_class, 'rb'))
	local data = file:read('*all')
	print(data)
	return bytes
end
