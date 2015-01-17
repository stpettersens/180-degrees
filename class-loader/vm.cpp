/*

The "VM" - a front end to the classloader.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

#include <iostream>
#include <cstring>
#include <string>
#include "boost/version.hpp"
#include "classloader.h"

#define VM_VERSION "1.0"

typedef char BYTE;

using namespace std;

void displayVersion() {
	
	cout << "Java \"VM\" v. " << VM_VERSION << " (using Boost "
	<< BOOST_VERSION / 100000 << "." 
	<< BOOST_VERSION / 100 % 1000 << "."
	<< BOOST_VERSION % 100 << ")." << endl;
	exit(0);
}

void loadClassFile(string claSS, bool dump) {

	ClassLoader classLoader;
	classLoader.load(claSS + ".class", dump);
}

int main(int argc, char* argv[]) {
	
	if(argc == 1) cout << "Usage: vm -c [-d] <classFile>" << endl;

	else if(argc > 1 && argc < 7) {

		for(int i = 1; i < argc; ++i) {

			if(strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--class") == 0) {
				if(strcmp(argv[i+1], "-d") == 0 || strcmp(argv[i+1], "--dump") == 0) {

					loadClassFile(string(argv[i+2]), true);
				}
				else {

					loadClassFile(string(argv[i+1]), false);
				}
			}
			else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {

				displayVersion();
			}
		}
	}

	return 0;
}
