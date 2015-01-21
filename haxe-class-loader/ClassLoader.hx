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
			var hexregx = ~/[0-9A-F]{2}/gi;
			hexregx.match(sbytes);
			trace(hexregx.matched(1));
			//var i: Int = 1;
			//while(i < 5) {
				//bytes.push(hexregx.matched(i));
				//++i;
			//}
		}
		else {
			Lib.println('\nCannot open file: $the_class');
			Lib.println('It does not exist or is inaccessible.\n');
			Sys.exit(-1);
		}
		return bytes;
	}

	/**
	 * Set a section of the loaded Java classfile stored object (cf).
	*/
	function setClassSection(start: Int, end: Int, base: Int): String {
		var fvalue: String = "";
		var value: Array<String> = [];
		var i: Int = start;
		while(i < end ) {
			value.push(classContents[i]);
			++i;
		}
		for(s in 0 ... value.length) {
			fvalue += value[s];
		}
		if(base == 10) { 
			var value: Int = Std.parseInt(fvalue);
			fvalue = '0x$value';
		}
		return fvalue;
	}

	/**
	 * Set magic number for loaded Java classfile.
	*/
	function setMagicNumber() {
		var magic: String = setClassSection(0, 4, 16);
		cf.setMagicNumber(magic);
	}	

	/**
	 * Set minor classfile version (e.g. 0).
	*/
	function setMinorVersion(): Void {
		var minorVer: String = setClassSection(4, 6, 10);
		cf.setMinorVersion(Std.parseInt(minorVer));
	}

	/**
	 * Set major classfile version (e.g. 51).
	*/
	function setMajorVersion(): Void {
		var majorVer: String = setClassSection(6, 8, 10);
		cf.setMajorVersion(Std.parseInt(majorVer));
	}

	/**
	 * Set constant pool count for classfile.
	*/
	function setConstantPoolCount() {
		var constPoolCount: String = setClassSection(8, 10, 10);
		cf.setConstantPoolCount(Std.parseInt(constPoolCount));
	}

	/**
	 * Set constant pool table for classfile.
	*/
	function setConstantPoolTable() {
		var n: Int = 10;
		var x: Int = 1;
		var y: Int = cf.getCPCOUNT() * 9;

		while(n < y) {
			var cc = Std.parseInt(classContents[n] + classContents[n+1]);
			trace(cc);
			++n;
		}
	}

	/**
	 * Constructor for ClassLoader.
	*/
	public function new(): Void { 

		cf = new ClassFile();
	}

	/**
	 * Load a Java classfile and dump loaded structure if specified.function
	*/
	public function load(_class: String, dump: Bool): Void {

		the_class = _class;
		classContents = readClassBytes();
		setMagicNumber();

		// ******************************************************************
		var magic: String  = cf.getMagicNumber();
		Lib.println('\nMagic number (hex) = 0x$magic');
		//  *****************************************************************

		if(cf.checkMagicNumber()) {
			Lib.println("");
			setMinorVersion();
			setMajorVersion();

			// **************************************************************
			var minorVer: Int = cf.getMinorVersion();
			Lib.println('Minor version = $minorVer');

			var majorVer: Int = cf.getMajorVersion();
			Lib.println('Major version = $majorVer');
			// **************************************************************

			setConstantPoolCount();
			setConstantPoolTable();
		}
	}
}
