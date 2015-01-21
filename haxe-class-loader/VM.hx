/*

The "VM" - a front end to the classloader.
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

class VM {

	static var vm_version: String = "1.0";

	static function displayVersion(): Void {

		Lib.println("Java \"VM\" v. " + vm_version + "\n");
		Sys.exit(0);
	}

	static function loadClassFile(_class: String, dump: Bool): Void {

		var classloader: ClassLoader = new ClassLoader();
		classloader.load(_class + ".class", dump);
	}

	public static function main(): Void {

		if(Sys.args()[0] == null) Lib.println("Usage: VM -c [-d] <classFile>\n");

		else if(Sys.args()[0] == "-v" || Sys.args()[0] == "--version") {
			displayVersion();
		}

		for(i in 0 ... Sys.args().length) {
			if(Sys.args()[i] == "-c" || Sys.args()[i] == "--class") {
				if(Sys.args()[i+1] == '-d' || Sys.args()[i+1] == '--dump') {
					loadClassFile(Sys.args()[i+2], true);
				}
				else {
					loadClassFile(Sys.args()[i+1], false);
				}
			}
		}
	}
}
