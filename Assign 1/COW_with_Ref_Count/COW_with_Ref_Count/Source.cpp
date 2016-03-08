// Main function for Copy on write implementation with reference counting

#include "StringBuffer.h"
#include <cstdlib>
#include <cstring>
#include <iostream>



using namespace std;

int main(int argc, char** argv) {
	//create a smart string
	//    String ss;
	//create a smart string with const char*
	char* hello = "hello";
	StringBuffer* obj = new StringBuffer(hello, 5);
	StringBuffer* obj2 = new StringBuffer();

	*obj2 = *obj;
	// Checking Append Fucntion
	obj2->append('h'); // 1st character append to obj 2
	obj2->append('w'); // 2nd character appedn to obj 2
	// Checking Length Function
	cout << "Copy on Write Implementation wiht Reference Counting "<< std::endl;
	cout << "Object 1 Length =" << obj->length() << std::endl;
	cout << "Object 2 Length =" << obj2->length() << std::endl;
	std::cout << "new ss charAt 0 = " << obj->charAt(0) << std::endl;


	getchar();
	return 0;
}

