#!/usr/bin/env python
"""
ClassLoader for "VM" front end.
Ported from C++ to Python.

Copyright 2015 Sam Saint-Pettersen

Released under the MIT/X11 License.
Please see LICENSE file.
"""
import sys
import re
from os import path
from classfile import ClassFile

class ClassLoader:

	classContents = []
	cf = the_class = ''

	def __init__(self):
		cf = ClassFile()

	def load(self, _class, dump):

		self.the_class = _class
		self.classContents = self.readClassBytes()
		self.setMagicNumber()

		# ----------------------------------------------------------------------------------------
		magic = cf.getMagicNumber()
		print('\nMagic number (hex) = {0} (dec: {1})'.format(magic, format(magic, '02x')))
		# ----------------------------------------------------------------------------------------

		if cf.checkMagicNumber():
			print('')
			self.setMinorVersion()
			self.setMajorVersion()

			# ------------------------------------------------------------------------------------
			minorVer = cf.getMinorVersion()
			print('Minor version = {0} (hex: {1})'.format(minorVer, format(minorVer, '02x')))

			majorVer = cf.getMajorVersion()
			print('Major version = {0} (hex: {1})'.format(majorVer, format(majorVer, '02x')))
			# ------------------------------------------------------------------------------------

	def readClassBytes(self):

		bytes = []
		if path.isfile(self.the_class):
			bytes_read = open(self.the_class, 'rb').read()
			for byte in bytes_read: 
				bytes.append(repr(byte))
		else:
			print('\nCannot open file: {0}'.format(self.the_class))
			print('It cannot not exist or is inaccessible.')
			sys.exit(-1)

		return bytes

	#
	# Set a section of the loaded Java classfile stored object (cf).
	#
	def setClassSection(self, start, end, base):
		fvalue = ''
		value = []
		i = start
		while(i < end):
			x = int(self.classContents[i], 16)
			value.append(x)
			i += 1

		s = ''
		for v in value:
			if base == 16: s = format(v, '02x')
			elif base == 10: s = str(v)
			fvalue += s

		return fvalue

	#
	# Set and return a constant pool array.
	#
	def setConstantPoolArray(self, tag, data1, data2):
		array = []
		array.append(tag)
		if data2 == '':
			array.append(data1)
		else:
			array.append('{0}{1}'.format(data1, data2))

		print('tag: {0}'.format(array[0]))
		print('>>>: {0}\n'.format(array[1]))
		return array

	#
	# Get UTF-8 character for decimal integer value.
	#
	def getUTF8Char(self, dec):
		return str(unichr(dec))

	#
	# Look up word mnemonic instruction from bytecode instruction.
	#
	def lookupMnemonicInstruction(self, bytecode):
		return "instruction" # TODO

	#
	# Set magic number for loaded Java classfile.
	#
	def setMagicNumber(self):
		magic = self.setClassSection(0, 4, 16)
		print(magic)
		cf.setMagicNumber(int(magic, 16))

	#
	# Set minor classfile version (e.g. 0).
	#
	def setMinorVersion(self):
		minorVer = self.setClassSection(4, 6, 10)
		cf.setMinorVersion(int(minorVer))

	#
	# Set major classfile version (e.g. 51).
	#
	def setMajorVersion(self):
		majorVer = self.setClassSection(6, 8, 10)
		cf.setMajorVersion(int(majorVer))

	#
	# Set constant pool count for classfile.
	#
	def setConstantPoolCount(self):
		constPoolCount = self.setClassSection(8, 10, 10)
		cf.setConstantPoolCount(int(constPoolCount))

	#
	# Get a hexadecimal value for a classfile byte offset.
	#
	def getHexadecimalValue(self, i, length):
		value = ''
		z = 2
		j = 0
		while j < length:
			_byte = int(self.classContents[i+z])
			if _byte >= 1 and _byte < 11 and _byte != 2: break
			value += format(_byte, '02x')
			classContents[i+z] = 0
			z += 1

		return value

	#
	# Get hexadecimal values for a classsfile byte offset.
	#
	def getHexadecimalValues(self, i, length):
		values = []
		z = 2
		j = 0
		while j < length:
			_byte = int(self.classContents[i+z])
			if _byte >= 1 and _byte < 11 and _byte != 2: break
			values.append(str(_byte))
			classContents[i+z] = 0
			z += 1

		return values

	#
	# Set constant pool table for classfile.
	#
	def setConstantPoolTable(self):
		constPoolTable = []
		n = 10
		x = 1
		y = cf.getCPCOUNT() * 9
		i = n
		while i < y:
			tag = cf.getTag(int(self.classContents[i]))
			_object = []

			if tag == 'Methodref':
				byte1 = int(self.classContents[i+2])
				byte2 = int(self.classContents[i+4])
				self.classContents[i+2] = 0
				self.classContents[i+4] = 0
				_object = []
				_object = self.setConstantPoolArray(tag, str(byte1), str(byte2))
				cf.setCPSIZE(5, 'Methodref')

			elif tag == 'Class':
				_object = []
				_object = self.setConstantPoolArray(tag, str(int(self.classContents[i+2])), '')
				self.classContents[i+2] = 0
				cf.setCPSIZE(3, 'Class')

			elif tag == 'Integer':
				integer = int(self.getHexadecimalValue(i, 4), 16)
				# ------------------------------------------------------------------------------
				print('Integer is {0} (hex: {1})\n'.format(integer, format(integer, '02x')))
				# ------------------------------------------------------------------------------
				r = 1
				while r <= 4:
					self.classContents[i+r] = 0
					r += 1

				_object = []
				_object = self.setConstantPoolArray(tag, str(integer), '')
				cf.setCPSIZE(5, 'Integer')

			elif tag == 'String':
				_object = []
				_object = self.setConstantPoolArray(tag, str(int(self.classContents[i+2])), '')
				cf.setCPSIZE(3, 'String')

			elif tag == 'NameAndType':
				byte1 = int(classContents[i+2])
				byte2 = int(classContents[i+4])
				_object = []
				_object = self.setConstantPoolArray(tag, str(byte1), str(byte2))
				cf.setCPSIZE(5, 'NameAndType')

			elif tag == 'Utf8':
				utf8ByteLength = 3
				size = int(classContents[i+2])

				# -------------------------------------------------------
				print('Declared UTF-8 size = {0}\n'.format(size))
				# -------------------------------------------------------

				self.classContents[i+2] = 0
				values = self.getHexadecimalValues(i+1, size)
				utf8 = ''
				for value in values:
					utf8int = int(value)
					utf8 += getUTF8Char(utf8int)
					utf8ByteLength += 1

				# ------------------------------------------------------
				print('Utf8 string is \"{0}\"\n'.format(utf8))
				# ------------------------------------------------------

				if len(utf8) > 2:
					print('Utf8 length: {0}'.format(utf8ByteLength))
					_object = []
					_object = self.setConstantPoolArray(tag, utf8, '')
					cf.setCPSIZE(utf8ByteLength, 'Utf8')

			i += 1
