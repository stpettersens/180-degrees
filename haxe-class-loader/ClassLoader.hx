/*

ClassLoader for "VM" front end.
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
import haxe.io.Bytes;
import sys.io.File;
import sys.FileSystem;

class ClassLoader {

	var classContents: Array<String>;
	var cf: ClassFile;
	var the_class: String;

	function readClassBytes(): Array<String> {

		var bytes: Array<String> = [];
		if(FileSystem.exists(the_class)) {

			var file = File.getBytes(the_class);
			var sbytes: String = file.toHex();
			for(byte in sbytes.split("")) {
				bytes.push(byte);
			}
		}
		else {
			Lib.println("\nCannot open file: " + the_class);
			Lib.println("It does not exist or is inaccessible.\n");
			Sys.exit(-1);
		}
		return bytes;
	}

	/**
	 * Set a section of the loaded Java classfile stored object (cf).
	*/
	function setClassSection(start: Int, end: Int, base: Int, magic: Bool): String {
		var fvalue: String = "";
		var value: Array<String> = [];
		var i: Int = start;
		while(i < end) {
			value.push(classContents[i]);
			++i;
		}
		for(s in 0 ... value.length) {
			fvalue += value[s];
		}
		return fvalue;
	}

	function setMagicNumber() {
		var magic: Int = 0;
		var smagic: String = setClassSection(0, 8, 16, true);
		trace(smagic);
		//cf.setMagicNumber(magic);
	}	
	

	public function new(): Void { // Constructor for ClassLoader.

		cf = new ClassFile();
	}

	/**
	 * Load a Java classfile and dump loaded structure if specified.function
	*/
	public function load(_class: String, dump: Bool): Void {

		the_class = _class;
		classContents = readClassBytes();
		setMagicNumber();
	}
}
