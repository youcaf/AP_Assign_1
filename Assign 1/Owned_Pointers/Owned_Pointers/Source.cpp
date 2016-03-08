// Main function for Owned Pointers

#include "StringBuffer.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	
	StringBuffer* obj = new StringBuffer();
	// Appending characters
	obj->append('a');
	obj->append('b'); 
	obj->append('c'); 
	obj->append('d'); 
	obj->append('e');
	cout << "Owned Pointer Implementation " << std::endl;
	// Checking Length Function
	cout << "Object 1 Length =" << obj->length() << std::endl;
	// Checking CharAt Function
	std::cout << "Object 1 charAt 0 = " << obj->charAt(0) << std::endl;

	getchar();
	return 0;
}

