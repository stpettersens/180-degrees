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
