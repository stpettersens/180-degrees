/*

The "VM" - a front end to the classloader.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

#include <iostream>
#include <iomanip> 
#include "classloader.h"

typedef char BYTE;

using namespace std;

int main() {
	//cout << "Usage: vm <classFile>" << endl;

	ClassLoader classLoader;
	classLoader.load("Main.class", true);

	//cout << classLoader.getMagicNumber() << endl;

	return 0;
}
