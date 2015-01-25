-- The "VM" - a front end to the ClassLoader.
-- Ported from C++ to Lua.
--
-- Copyright 2015 Sam Saint-Pettersen
--
-- Released under the MIT/X11 License.
-- Please see LICENSE file.

require 'classloader'

VM_VERSION = '1.0'

function displayVersion()
	print(string.format('Java \"VM\" v. %s', VM_VERSION))
	os.exit(0)
end

function loadClassFile(class, dump)
	local classLoader = ClassLoader.create()
	classLoader:load(string.format('%s.class', class), dump)
	os.exit(0)
end

function main()
	if #arg == 0 then 
		print('Usage: vm -c [-d] <classFile>\n') 
	else
		if arg[1] == '-v' or arg[1] == '--version' then
			displayVersion()
		end
		local i = 1
		while i < #arg do
			if arg[i] == '-c' or arg[i] == '--class' then
				if arg[i+1] == '-d' or arg[i+1] == '--dump' then
					loadClassFile(arg[i+2], true)
				else
					loadClassFile(arg[i+1], false)
				end
			end
		end
	end
	os.exit(0)
end

main()
