#pragma once
// Header fileCopy on Write Implementation with Reference Counting 
#include <iostream>

class strinB
{
public:
	char* string_buf;  //buffer string
	int _length;    //length of the string
	int _refcount;	//no of references
	strinB();			//constructor
};
class StringBuffer {

public:
	StringBuffer();  //default constructor
	~StringBuffer();				 //destructor; would delete the allocated buffer
	StringBuffer(const StringBuffer&); //constructor for shallow copying
	StringBuffer(char*, int);   //constructor to convert a char* to StringBuffer
	strinB* getstring_();
	char charAt(int) const;   //returns the character at the passed index
	int length() const;       //returns the length of the buffer
	void reserve(int);        //allocates memory for the string, according to the passed character length
	void append(char);        //appends a single character at the end
	
	StringBuffer& operator = (const StringBuffer&);

private:
	strinB*  string_;
};

