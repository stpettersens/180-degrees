/*
	Define a Java class file.
	180 degrees project: Day 1
	Copyright (c) 2014 Sam Saint-Pettersen
*/
struct ClassFile  {
	unsigned int magic; 				// u4: 0xCAFEBABE
	unsigned short minor_version; 		// u2
	unsigned short major_version;		// u2
	unsigned short constant_pool_count;	// u2
	/*cp_info constant_pool_count[constant_pool_count-1];
	unsigned int access_flags;
	unsigned int this_class;
	unsigned int super_class;
	unsigned int interfaces_count;
	unsigned int interfaces[interfaces_count];
	unsigned int fields_count;
	field_info fields[fields_count];
	unsigned int methods_count;
	method_info methods[methods_count];
	unsigned int attributes_count;
	attributes_info attributes[attributes_count];*/
};
