/*

The "VM" - a front end to the classloader.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

package main

import ( 
	"fmt"
	"os"
)

func displayVersion() {
	var VM_VERSION string = "1.0"
	fmt.Println(fmt.Sprintf("Java \"VM\" v. %v", VM_VERSION))
}

func loadClassFile(class string, dump bool) {
	classLoader := ClassLoader{}
	classLoader.load(fmt.Sprintf("%v.class", class), dump)
}

func main() {
	if(len(os.Args) == 1) { 
		fmt.Println("Usage: vm -c [-d] <classFile>") 

	} else if(len(os.Args) > 1 && len(os.Args) < 7) {
		for i := 0; i < len(os.Args); i++ {
			if(os.Args[i] == "-c" || os.Args[i] == "--class") {
				if(os.Args[i+1] == "-d" || os.Args[i+1] == "--dump") {
					loadClassFile(os.Args[i+2], true)
				
				} else {
					loadClassFile(os.Args[i+1], false)
				}

			} else if(os.Args[i] == "-v" || os.Args[i] == "--version") {
				displayVersion()
			}
		}
	}
}
