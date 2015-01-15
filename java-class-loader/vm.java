//package

/*

The "VM" - a front end to the classloader.
Ported from C++ to Java.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

class VM {

	private static String version = "1.0";

	private static void displayVersion() {

		System.out.println("Java \"VM\" v. " + version + "\n");
		System.exit(0);
	}

	private static void loadClassFile(String claSS, boolean dump) {

		ClassLoader classLoader = new ClassLoader();
		classLoader.load(String.format("%s.class", claSS), dump);
	}

	public static void main(String[] args) {

		if(args.length == 0) System.out.println("Usage: VM -c [-d] <classFile>");

		else if(args.length > 1 && args.length < 7) {

			for(int i = 0; i < args.length; ++i) {

				if(args[i].equals("-c") || args[i].equals("--class")) {
					if(args[i+1].equals("-d") || args[i+1].equals("--dump")) {

						loadClassFile(args[i+2], true);
					}
					else {

						loadClassFile(args[i+1], false);
					}
				}
			}
		}
	} 
}
