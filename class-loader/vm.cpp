/*

The "VM" - a front end to the classloader.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

#include <iostream>
#include "classloader.h"

using namespace std;

typedef char BYTE;

int main() {
	//cout << "Usage: vm <classFile>" << endl;

	ClassLoader classLoader;
	classLoader.load("Main.class", true);
	
	return 0;
}
