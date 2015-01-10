/*
	Check that a file exists with boost::filesystem.
*/

#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	if(argc == 0) cout << "Usage: exists <file>" << endl;
	if(argc > 0) {
		if(boost::filesystem::exists(argv[1])) {
			cout << "File: " << argv[1] << " exists." << endl;
		}
	}
	return 0;
 }
