/*

The "VM" - a front end to the classloader.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

#include <iostream>
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

int main() {
	
	//cout << "Usage: vm <classFile>" << endl;

	ClassLoader classLoader;
	classLoader.load("Main.class", true);

	return 0;
}
