
require 'classloader'
require 'classfile'

function main()
	local classLoader = ClassLoader.create()
	classLoader:load('Main.class', true)
end

main()
