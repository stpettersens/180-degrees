/*

The "VM" - a front end to the classloader.
Ported from C++ to Java.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/
//package io.stpettersen.classloader;

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
			int c;

			while((c = in.read()) != -1) {
				bytes.add(c);
			}
		}
		catch(IOException e) {
			System.out.println("\nCannot open file:");
			System.out.println(e.getMessage());
			System.exit(-1);
		}
		return bytes;
	}

	/**
	 * Set a section of the loaded Java classfile stored object (cf).
	*/
	String setClassSection(int start, int end, int base, boolean magic) {
		String fvalue = "";
		ArrayList<Integer> value = new ArrayList<Integer>();
		for(int i = start; i < end; ++i) {
			int x = classContents.get(i);
			value.add(x);
		}
		for(int i = 0; i < value.size(); ++i) {
			String s = "";
			if(base == 16) s = Integer.toHexString(value.get(i));
			if(base == 10) s = String.format("%s", value.get(i));
			fvalue += s;
		}
		return fvalue;
	}

	/**
	 * Set magic number for loaded Java classfile.
	*/
	void setMagicNumber() {
		String smagic = setClassSection(0, 4, 16, true);
		long magic = Long.parseLong(smagic, 16);
		cf.setMagicNumber(magic);
	}

	/**
	 * Load a Java classfile and dump  loaded structure if specified.
	*/
	void load(String claSS, boolean dump) {
		the_class = claSS;
		classContents = readClassBytes();
		System.out.println(Integer.toHexString(classContents.get(0)));
		long coffee = Long.parseLong("cafebabe", 16);
		System.out.println(coffee);
		System.out.println(Long.toHexString(coffee));
	}
}
