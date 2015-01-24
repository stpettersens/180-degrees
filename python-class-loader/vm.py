#!/usr/bin/env python
"""
The "VM" - a front end to the classloader.
Ported from C++ to Python.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.
"""
import argparse
from classloader import ClassLoader

VM_VERSION = '1.0'

def displayVersion():
	print('Java \"VM\" v. {0}'.format(VM_VERSION))

def displayInfo():
	print(__doc__)

def loadClassFile(_class, dump):

	classLoader = ClassLoader()
	classLoader.load('{0}.class'.format(_class), dump)

def VM(_class, dump, version, info):

	if _class == None and dump == False:
		if version == True and info == False:
			displayVersion()

		elif version == False and info == True:
			displayInfo()

	elif _class != None:
		loadClassFile(_class, dump)

# Handle any command line arguments.
parser = argparse.ArgumentParser(description='Java \"VM\" front-end.')
parser.add_argument('-c', '--class', action='store', dest='_class', metavar="_CLASS")
parser.add_argument('-d', '--dump', action='store_true', dest='dump')
parser.add_argument('-v', '--version', action='store_true', dest='version')
parser.add_argument('-i', '--info', action='store_true', dest='info')
argv = parser.parse_args()

VM(argv._class, argv.dump, argv.version, argv.info)
