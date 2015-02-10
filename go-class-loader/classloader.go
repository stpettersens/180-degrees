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
	"os"
	"strconv"
)

type ClassLoader struct {
	classContents []byte
	cf ClassFile
	the_class string
}

func (cl *ClassLoader) pass(err error) {
	// Pass an error message and do nothing with it!
}

func (cl *ClassLoader) readClassBytes() ([]byte) {
	if(cl.classExists()) {
		data, err := ioutil.ReadFile(cl.the_class)
		cl.pass(err)
		return data

	} else {
		fmt.Println(fmt.Sprintf("\nCannot open file: %v", cl.the_class))
		fmt.Println("It does not exist or is inaccessible.")
		os.Exit(-1)
	}
	return []byte { 0 }
}

/**
 * Check that classfile exists.
*/
func (cl *ClassLoader) classExists() (bool) {
	data, err := ioutil.ReadFile(cl.the_class)
	if(len(data) > 0) { 
		cl.pass(err)
		return true 
	}
	return false
}

/**
 * Set a section of the loaded Java classfile stored object (cf).
*/
func (cl *ClassLoader) setClassSection(start int, end int, base int) (string) {
	var fvalue string = ""
	value := make([]byte, 1)
	for i := 0; i < end; i++ {
		var x byte = cl.classContents[i]
		value = append(value, x)
	}
	for i := 0; i < len(value); i++ {
		var s string = ""
		if(base == 16) { s = fmt.Sprintf("%x", value[i]) }
		if(base == 10) { s = fmt.Sprintf("%d", value[i]) }
		fvalue += s
	}
	return fvalue
}

/**
 * Set magic number for loaded Java classfile.
*/
func (cl *ClassLoader) setMagicNumber() {
	smagic := cl.setClassSection(0, 4, 16)
	magic, err := strconv.ParseUint(smagic, 16, 32)
	cl.pass(err)
	cl.cf.setMagicNumber(uint32(magic))
}

/**
 * Set minor classfile version (e.g. 0).
*/
 func (cl *ClassLoader) setMinorVersion() {
 	sminorVer := cl.setClassSection(4, 6, 10)
 	minorVer, err := strconv.ParseUint(sminorVer, 10, 16)
 	cl.pass(err)
 	cl.cf.setMinorVersion(uint16(minorVer))
 }

 /**
  * Set major classfile version (e.g. 51).
 */
 func (cl *ClassLoader) setMajorVersion() {
 	smajorVer := cl.setClassSection(6, 8, 10)
 	majorVer, err := strconv.ParseUint(smajorVer, 10, 16)
 	cl.pass(err)
 	cl.cf.setMajorVersion(uint16(majorVer))
 }

/**
 * Load a Java classfile and dump loaded structure if specified.
*/
func (cl *ClassLoader) load(class string, dump bool) {
	cl.cf = ClassFile{}
	cl.the_class = class
	cl.classContents = cl.readClassBytes()
	cl.setMagicNumber()

	// ******************************************************************************
	var magic uint32 = cl.cf.getMagicNumber()
	fmt.Println(fmt.Sprintf("\nMagic number (hex) = 0x%X (dec: %d)", magic, magic))
	// ******************************************************************************

	if(cl.cf.checkMagicNumber()) {
		fmt.Println("\n")
		cl.setMinorVersion()
		//cl.setMajorVersion()

		// *******************************************************************************
		var minorVer uint16 = cl.cf.getMinorVersion()
		fmt.Println(fmt.Sprintf("Minor version = %d (hex: %x)\n", minorVer, minorVer))

		//var majorVer uint16 = cl.cf.getMajorVersion()
		//fmt.Println(fmt.Sprintf("Major version = %d (hex: %x)\n", majorVer, majorVer))
		// *******************************************************************************
	}
}
