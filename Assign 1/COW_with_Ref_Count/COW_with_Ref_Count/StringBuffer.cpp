// Copy on Write Implementation with Reference Counting 
#include "StringBuffer.h" // Including the header file 
#include <iostream>

// Constructor
StringBuffer::StringBuffer() 
{
	// Setting String Buffer to Null
	string_ = nullptr; 
}
// Destructor
StringBuffer::~StringBuffer() 
{
	// Checking ref count
	if (string_->_refcount == 1)
	{
		delete[] string_->string_buf;
		delete string_;
	}
	else
	{
		string_->_refcount--;
	}
}
// For getting String
strinB* StringBuffer::getstring_() 
{
	return string_;
}
StringBuffer::StringBuffer(const StringBuffer& obj) {

	// Shallow Copying
	string_->_length = obj.length();
	string_->string_buf = new char[string_->_length];
	for (int i = 0; i<string_->_length; i++)
	{
		string_->string_buf[i] = obj.charAt(i);
	}
}
// Constructor converting char to Smart String
StringBuffer::StringBuffer(char* ptr, int length)
{
	
	string_ = new strinB;
	string_->string_buf = new char[length];
	string_->_length = length;
	for (int i = 0; i < length - 1; i++)
	{
		string_->string_buf[i] = ptr[i];
	}
}

char StringBuffer::charAt(int index) const
{
	// Checking the length given is less then the string length
	if (index < string_->_length) 
	{
		return *(string_->string_buf + index);
	}
	else {

		throw"\n\n\t##Array Index Out Of Bounds.\n\n";
	}

}
// Length of the String
int StringBuffer::length() const 
{
	return string_->_length;
}

void StringBuffer::reserve(int length)
{
	// -> allocates memory of character length size
	string_ = new strinB;
	string_->string_buf = new char[length];
}

void StringBuffer::append(char c)
{
	// -> appendingcharacter at end of string
	if (string_->_refcount>1)
	{
		strinB* str1 = new strinB;
		str1->_length = string_->_length + 1;
		str1->string_buf = new char[str1->_length];
		for (int i = 0; i < string_->_length; i++)
		{
			str1->string_buf[i] = string_->string_buf[i];
		}
		str1->string_buf[string_->_length] = c;
		string_->_refcount--;
		string_ = str1;

	}
	else
	{

		char* str1 = string_->string_buf;
		string_->_length++;
		string_->string_buf = new char[string_->_length];
		for (int i = 0; i < string_->_length - 1; i++)
		{
			string_->string_buf[i] = str1[i];
		}
		string_->string_buf[string_->_length - 1] = c;
		delete[] str1;

	}


}
// Constructor
strinB::strinB()
{
	string_buf = nullptr;
	_length = 0;
	_refcount = 1;
}
// Operator Overloading
StringBuffer& StringBuffer::operator = (const StringBuffer& obj)
{
	
	string_ = obj.string_;
	string_->_refcount++;
	return *this;
}



