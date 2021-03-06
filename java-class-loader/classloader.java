//package

/*

ClassLoader for "VM" front end.
Ported from C++ to Java.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/
import java.util.ArrayList;
import java.io.FileInputStream;
import java.io.IOException;

class ClassLoader {

	private ArrayList<Integer> classContents;
	private ClassFile cf;
	private String the_class;

	private ArrayList<Integer> readClassBytes()  {

		ArrayList<Integer> bytes = new ArrayList<Integer>();
		FileInputStream in = null;

		try {
			in = new FileInputStream(the_class);
			int c = 0;

			while((c = in.read()) != -1) {
				bytes.add(c);
			}
		}
		catch(IOException e) {
			System.out.println(String.format("\nCannot open file: %s", the_class));
			System.out.println(e.getMessage());
			System.exit(-1);
		}
		return bytes;
	}

	/**
	 * Set a section of the loaded Java classfile stored object (cf).
	*/
	private String setClassSection(int start, int end, int base, boolean magic) {
		String fvalue = "";
		ArrayList<Integer> value = new ArrayList<Integer>();
		for(int i = start; i < end; ++i) {
			int x = classContents.get(i);
			value.add(x);
		}
		for(int i = 0; i < value.size(); ++i) {
			String s = "";
			if(base == 16) s = Integer.toHexString(value.get(i));
			if(base == 10) s = String.format("%d", value.get(i));
			fvalue += s;
		}
		return fvalue;
	}

	/**
	 * Set and return a constant pool array (ArrayList).
	*/
	private ArrayList<String> setConstantPoolArray(String tag, String data1, String data2) {
		ArrayList<String> array = new ArrayList<String>();
		if(data2 == "") {
			array.add(tag);
			array.add(data1);
		}
		else {
			array.add(tag);
			array.add(data1 + "," + data2);
		}
		System.out.println(String.format("tag: %s", array.get(0)));
		if(tag == "Integer") System.out.println(String.format(">>> %d\n", Integer.parseInt(array.get(1), 16)));
		else System.out.println(String.format(">>> %s\n", array.get(1)));
		return array;
	}

	/**
	 * Get UTF-8 character for decimal integer value.
	*/
	private char getUTF8Char(int dec) {
		return (char)dec;
	}

	private String lookupMnemonicInstruction(int bytecode) {
		return lookupMnemonicInstruction(String.format("%d", bytecode));
	}

	private String lookupMnemonicInstruction(String bytecode) {
		return "instruction"; // TODO
	}

	/**
	 * Set magic number for loaded Java classfile.
	*/
	private void setMagicNumber() {
		String smagic = setClassSection(0, 4, 16, true);
		long magic = Long.parseLong(smagic, 16);
		cf.setMagicNumber(magic);
	}

	/**
	 * Set minor classfile version (e.g. 0).
	*/
	private void setMinorVersion() {
		String minorVer = setClassSection(4, 6, 10, false);
		cf.setMinorVersion(Integer.parseInt(minorVer));
	}

	/**
	 * Set major classfile version (e.g. 51).
	*/
	private void setMajorVersion() {
		String majorVer = setClassSection(6, 8, 10, false);
		cf.setMajorVersion(Integer.parseInt(majorVer));
	}

	/**
	 * Set constant pool count for classfile.
	*/
	private void setConstantPoolCount() {
		String constPoolCount = setClassSection(8, 10, 10, false);
		cf.setConstantPoolCount(Integer.parseInt(constPoolCount));
	}

	/**
	 * Get a hexadecimal value for a classfile byte offset.
	*/
	private String getHexadecimalValue(int i, int length) {
		String value = "";
		int z = 2;
		for(int j = 0; j < length; ++j) {
			int _byte = classContents.get(i+z);
			if(_byte >= 1 && _byte < 11 && _byte != 2) {
				break;
			}
			String s = Integer.toHexString(_byte);
			classContents.set(i+z, 0);
			value += s;
			++z;
		}
		return value;
	}

	/**
	 * Get a hexadecimal values for a classfile byte offset.
	*/
	private ArrayList<String> getHexadecimalValues(int i, int length) {
		ArrayList<String> values = new ArrayList<String>();
		int z = 2;
		for(int j = 0; j < length; ++j) {
			int _byte = classContents.get(i+z);
			if(_byte >= 1 && _byte < 11 && _byte != 2) {
				break;
			}
			String s = Integer.toHexString(_byte);
			values.add(s);
			classContents.set(i+z, 0);
			++z;
		}
		return values;	
	}

	/**
	 * Set constant pool table for classfile.
	*/
	private void setConstantPoolTable() {

		ArrayList<String> constPoolTable = new ArrayList<String>();
		int n = 10;
		int x = 1;
		int y = cf.getCPCOUNT() * 9;

		for(int i = n; i < y; ++i) {

			String tag = cf.getTag(classContents.get(i));
			ArrayList<String> object = new ArrayList<String>();

			switch(tag) {

				case "Methodref":
					int byte1 = classContents.get(i+2);
					int byte2 = classContents.get(i+4);
					classContents.set(i+2, 0); // Set byte to 9 to prevent re-read of byte.
					classContents.set(i+4, 0);
					String sbyte1 = String.format("%d", byte1);
					String sbyte2 = String.format("%d", byte2);
					object.clear();
					object = setConstantPoolArray(tag, sbyte1, sbyte2);
					cf.setCPSIZE(5, "Methodref");
					break;

				case "Class":
					String sbyte = String.format("%d", classContents.get(i+2));
					object.clear();
					object = setConstantPoolArray(tag, sbyte, "");
					classContents.set(i+2, 0);
					cf.setCPSIZE(3, "Class");
					break;

				case "Integer":

					int integer = Integer.parseInt(getHexadecimalValue(i, 4), 16);
					String sint = Integer.toHexString(integer);

					// *******************************************************************************
					System.out.println(String.format("Integer is: %d (hex: %s)\n", integer, sint));
					// *******************************************************************************

					for(int r = 1; r <= 4; ++r) {
						classContents.set(i+r, 0);
					}
	 		
					object.clear();
					object = setConstantPoolArray(tag, sint, "");
					cf.setCPSIZE(5, "Integer");
					break;

				case "String":
					String str = String.format("%s", classContents.get(i+2));
					object.clear();
					object = setConstantPoolArray(tag, str, "");
					cf.setCPSIZE(3, "String");
					break;

				case "NameAndType":
					int byteA = classContents.get(i+2);
					int byteB = classContents.get(i+4);
					String sbyteA = String.format("%d", byteA);
					String sbyteB = String.format("%d", byteB);
					classContents.set(i+2, 0);
					classContents.set(i+4, 0);
					object.clear();
					object = setConstantPoolArray(tag, sbyteA, sbyteB);
					cf.setCPSIZE(5, "NameAndType");
					break;

				case "Utf8":
					int utf8ByteLength = 3;
					int size = classContents.get(i+2);

					// ********************************************************************
					System.out.println(String.format("Declared UTF-8 size = %d", size));
					// ********************************************************************

					classContents.set(i+2, 0);
					ArrayList<String> values = getHexadecimalValues(i+1, size);
					String utf8 = "";
					for(int z = 0; z < values.size(); ++z) {
						int utf8int = Integer.parseInt(values.get(z), 16);
						utf8 += getUTF8Char(utf8int);
						++utf8ByteLength;
					}

					// ********************************************************************
					// System.out.println(String.format("Utf8 string is: \"%s\"", utf8));
					// System.out.println("");
					// ********************************************************************

					if(utf8.length() > 2) {
						System.out.println(String.format("Utf-8 length: %d", utf8ByteLength));
						object.clear();
						object = setConstantPoolArray(tag, utf8, "");
						cf.setCPSIZE(utf8ByteLength, "Utf8");
					}
					break;
			}
		}
	}

	/**
	 * Set access flags for classfile.
	*/
	private void setAccessFlags() {
		int cpsize = cf.getCPSIZE();
		int accessFlags = classContents.get(cpsize + 10) + classContents.get(cpsize + 11);
		cf.setAccessFlags(accessFlags);
	}

	/**
	 * Set this class for classfile.
	*/
	private void setThisClass() {
		int cpsize = cf.getCPSIZE();
		int thisClass = classContents.get(cpsize + 12) + classContents.get(cpsize + 13);
		cf.setThisClass(thisClass);
	}

	/**
	 * Set super class for classfile.
	*/
	private void setSuperClass() {
		int cpsize = cf.getCPSIZE();
		int superClass = classContents.get(cpsize + 14) + classContents.get(cpsize + 15);
		cf.setSuperClass(superClass);
	}

	/**
	 * Set interfaces count.
	*/
	private void setInterfacesCount() {
		int cpsize = cf.getCPSIZE();
		int interfacesCount = classContents.get(cpsize + 16) + classContents.get(cpsize + 17);
		cf.setStartByte(18);
		cf.setInterfacesCount(interfacesCount);
	}

	/**
	 * Push any interfaces to intefaces table.
	*/
	private void pushInterfaces() {
		int cpsize = cf.getCPSIZE();
		int x = cf.getStartByte();
		int interfacesCount = cf.getInterfacesCount();
		if(interfacesCount > 0) {
			for(int i = 0; i < interfacesCount; ++i) {
				int _interface = classContents.get(cpsize + x) + classContents.get(cpsize + (x + 1));
				cf.pushInterface(_interface);
				++x;
			}
			cf.setStartByte(x + 1);
		}
	}

	/**
	 * Set fields count.
	*/
	private void setFieldsCount() {
		int cpsize = cf.getCPSIZE();
		int x = cf.getStartByte();
		int fieldsCount = classContents.get(cpsize + x) + classContents.get(cpsize + (x + 1));
		cf.setStartByte(x + 2);
		cf.setFieldsCount(fieldsCount);
	}

	/**
	 * Push any fields to fields table.
	*/
	private void pushFields() {
		int cpsize = cf.getCPSIZE();
		int x = cf.getStartByte();
		int fieldsCount = cf.getFieldsCount();
		if(fieldsCount > 0) {
			for(int i = 0; i < fieldsCount; ++i) {
				int field = classContents.get(cpsize + x) + classContents.get(cpsize + (x + 1));
				cf.pushField(field);
				++x;
			}
			cf.setStartByte(x + 1);
		}
	}

	/**
	 * Set methods count.
	*/
	private void setMethodsCount() {
		int cpsize = cf.getCPSIZE();
		int x = cf.getStartByte();
		int methodsCount = classContents.get(cpsize + x) + classContents.get(cpsize + (x + 1));
		cf.setStartByte(x + 2);
		cf.setMethodsCount(methodsCount);
	}

	/**
	 * Push any methods to methods table.
	*/
	private void pushMethods() {
		int cpsize = cf.getCPSIZE();
		int x = cf.getStartByte();
		int methodsCount = cf.getMethodsCount();
		/*if(methodsCount < 0) {
			for(int i = 0; i < methodsCount; ++i) {
				int method = classContents.get(cpsize + x) + classContents.get(cpsize + (x + 1));
				cf.pushMethod(method);
				++x;
			}
			cf.setStartByte(x + 1);
		}*/
	}

	/**
	 * Set attributes count.
	*/
	private void setAttributesCount() {
		int cpsize = cf.getCPSIZE();
		int x = cf.getStartByte();
		int attribCount = classContents.get(cpsize + x) + classContents.get(cpsize + (x + 1));
		cf.setStartByte(x + 2);
		cf.setAttributesCount(attribCount);
	}

	/**
	 * Push any attributes to attributes table.
	*/
	private void pushAttributes() {
		int cpsize = cf.getCPSIZE();
		int x = cf.getStartByte();
		/*int attribsCount = cf.getAttributesCount();
		if(attribsCount > 0) {
			for(int i = 0; i < attribsCount; ++i) {
				int attribute = classContents.get(cpsize + x) + classContents.get(cpsize + (x + 1));
				cf.pushAttribute(attribute);
				++x;
			}
			cf.setStartByte(x + 20);
		}*/
	}

	/**
	 * Set bytecodes count.
	*/
	private void setBytecodesCount() {
		int cpsize = cf.getCPSIZE();
		int x = cf.getStartByte();
		int bytecodesCount = classContents.get(cpsize + x) + classContents.get(cpsize + (x + 1));
		cf.setStartByte(x + 20);
		cf.setBytecodesCount(bytecodesCount);
	}

	/**
	 * Push bytecodes to bytecodes table.
	*/
	private void pushBytecodes() {
		int cpsize = cf.getCPSIZE();
		int x = cf.getStartByte();
		int bytecodesCount = cf.getBytecodesCount();
		if(bytecodesCount > 0) {
			for(int i = 0; i < bytecodesCount; ++i) {
				int bytecode = classContents.get(cpsize + x) + classContents.get(cpsize + (x + 1));
				cf.pushBytecode(bytecode);
				++x;
			}
		}
		cf.setStartByte(x);
	}


	ClassLoader() { // Constructor for ClassLoader.

		cf = new ClassFile();
	}

	/**
	 * Load a Java classfile and dump  loaded structure if specified.
	*/
	void load(String claSS, boolean dump) {
		
		the_class = claSS;
		classContents = readClassBytes();
		setMagicNumber();

		// ****************************************************************************************
		long magic = cf.getMagicNumber();
		String hmagic = Long.toHexString(magic);
		System.out.println(String.format("\nMagic number (hex) = %s (dec: %d)", hmagic, magic));
		// ****************************************************************************************

		if(cf.checkMagicNumber()) {
			System.out.println("");
			setMinorVersion();
			setMajorVersion();

			// *****************************************************************************************
			int minorVer = cf.getMinorVersion();
			String hminorVer = Integer.toHexString(minorVer);
			System.out.println(String.format("Minor version = %d (hex: %s)", minorVer, hminorVer));

			int majorVer = cf.getMajorVersion();
			String hmajorVer = Integer.toHexString(majorVer);
			System.out.println(String.format("Major version = %d (hex: %s)\n", majorVer, hmajorVer));
			// *****************************************************************************************

			setConstantPoolCount();
			setConstantPoolTable();;
			setAccessFlags();
			setThisClass();
			setSuperClass();
			setInterfacesCount();
			pushInterfaces();
			setFieldsCount();
			pushFields();
			setMethodsCount();
			pushMethods();
			setAttributesCount();
			pushAttributes();
			setBytecodesCount();
			pushBytecodes();

			// *****************************************************************************************
			System.out.println(String.format("CP_COUNT  = %d", cf.getCPCOUNT()));
			System.out.println(String.format("CP_SIZE = %d", cf.getCPSIZE()));

			String af = Integer.toHexString(cf.getAccessFlags());
			System.out.println(String.format("Access flags: %s", af));
			System.out.println(String.format("This class: %d", cf.getThisClass()));
			System.out.println(String.format("Super class: %d", cf.getSuperClass()));
			System.out.println(String.format("Interfaces count: %d", cf.getInterfacesCount()));
			System.out.println(String.format("Fields count: %d", cf.getFieldsCount()));
			System.out.println(String.format("Methods count: %d", cf.getMethodsCount()));
			System.out.println(String.format("Attributes count: %d", cf.getAttributesCount()));
			System.out.println(String.format("Bytecodes count: %d", cf.getBytecodesCount()));

			System.out.println("\nBytecodes:\n");
			ArrayList<Integer> bytecodes = cf.pullBytecodes();
			for(int i = 0; i < cf.getBytecodesCount(); ++i) {
				String hbytecode = Integer.toHexString(bytecodes.get(i));
				System.out.println(hbytecode);
			}
			// *****************************************************************************************
		}
		else {
			System.out.println("Invalid Java classfile. Terminating now...");
			System.exit(-1);
		}
	}
}
