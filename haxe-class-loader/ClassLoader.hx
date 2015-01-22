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
			var hex: String = "";  
			var i: Int = 1;
			while(i <= sbytes.length / 2) {
				hex += "([0-9a-f]{2})"; // Match a hexadecimal notated byte.
				++i;
			}
			var hexr = new EReg(hex, "i");
			hexr.match(sbytes);
			i = 1;
			while(i <= sbytes.length / 2) {
				bytes.push(hexr.matched(i));
				++i;
			}
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
	 * Set and return a constant pool array.
	*/
	function setConstantPoolArray(tag: String, data1: String, data2: String): Array<String> {
		var array: Array<String> = [];
		if(data2 == "") {
			array.push(tag);
			array.push(data1);
		}
		else {
			array.push(tag);
			array.push('$data1,$data2');
		}
		Lib.println("tag: " + array[0]);
		Lib.println(">>> " + array[1] + "\n");
		return array;
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

		var i: Int = n;
		while(i < y) {

			var cc: Int = Std.parseInt('0x' + classContents[i]);
			var tag: String = cf.getTag(cc);
			var object: Array<String> = [];

			switch tag {

				case "Methodref":
					var byte1: Int = Std.parseInt('0x' + classContents[i+2]);
					var byte2: Int = Std.parseInt('0x' + classContents[i+4]);
					classContents[i+2] = "0";
					classContents[i+4] = "0";
					object = [];
					object = setConstantPoolArray(tag, Std.string(byte1), Std.string(byte2));
					cf.setCPSIZE(5, "Methodref");

				case "Class":
					object = [];
					var byte1: Int = Std.parseInt('0x' + classContents[i+2]);
					object = setConstantPoolArray(tag, Std.string(byte1), "");
					classContents[i+2] = "0";
					cf.setCPSIZE(3, "Class");

				case "Integer":
					var integer: Int = Std.parseInt('0xA');
			}
			++i;
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
			Lib.println('Major version = $majorVer\n');
			// **************************************************************

			setConstantPoolCount();
			setConstantPoolTable();
		}
	}
}
