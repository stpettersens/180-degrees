/*

The "VM" - a front end to the classloader.
Ported from C++ to Java.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/
//package io.stpettersen.classloader;

class VM {

	private static String version = "1.0";

	private static void displayVersion() {

		System.out.println("Java \"VM\" v. " + version + "\n");
	}

	public static void main(String[] args) {

		System.out.println("Usage: vm <classFile>\n");
	} 
}
