/*

ClassLoader for "VM" front end.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.

*/

package main

import (
	"fmt"
	"io/ioutil"
)

type ClassLoader struct {
	classContents []byte
	cf ClassFile
	the_class string
}

func (cl *ClassLoader) readClassBytes() ([]byte) {
	fmt.Println(cl.classExists())
	return []byte { 0, 0, 0 }
}

/**
 * Check that classfile exists.
*/
func (cl *ClassLoader) classExists() (bool) {
	data, err := ioutil.ReadFile(cl.the_class)
	fmt.Println(data)
	if(len(data) > 0) { 
		fmt.Println(err)
		return true 
	}
	return false
}

/**
 * Set magic number for loaded Java classfile.
*/
func (cl *ClassLoader) setMagicNumber() {

}

/**
 * Load a Java classfile and dump loaded structure if specified.
*/
func (cl *ClassLoader) load(class string, dump bool) {
	cl.the_class = class
	cl.classContents = cl.readClassBytes()
	cl.setMagicNumber()
}
