// Copy on write with implementation of reference linking
#include "StringBuffer.h"
#include <iostream>

StringBuffer::StringBuffer() 
{
	_stringB = nullptr; 
}

StringBuffer::~StringBuffer() // 
{
	if (_stringB->_refcount == 1)
	{
		delete[] _stringB->string_buf;
		delete _stringB->_reflink;
		delete _stringB;
	}
	else
	{
		_stringB->_refcount--;
		StringBuffer* add = this;
		if (_stringB->_reflink->_address == this)
		{
			reflink* temp = _stringB->_reflink;
			_stringB->_reflink = _stringB->_reflink->next;
			delete temp;
		}

		else {

			reflink* ptr = _stringB->_reflink;
			reflink* prev = NULL;

			while (ptr)
			{
				if (ptr->_address == this)
				{
					prev->next = ptr->next;
					delete ptr;
					break;
				}
				prev = ptr;
				ptr = ptr->next;
			}

		}
	}

}
StringBuffer::StringBuffer(const StringBuffer& obj) {

	
	_stringB->strlen = obj.length();
	_stringB->string_buf = new char[_stringB->strlen];
	for (int i = 0; i<_stringB->strlen; i++)
	{
		_stringB->string_buf[i] = obj.charAt(i);
	}
	reflink* rlinking = new reflink;
	rlinking->_address = this;
	rlinking->next = NULL;
	if (_stringB->_reflink == NULL)
	{
		_stringB->_reflink = rlinking;
	}
	else
	{
		reflink* ptr = _stringB->_reflink;
		reflink*  prev = NULL;
		while (ptr)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		prev->next = rlinking;
	}
}

StringBuffer::StringBuffer(char* ptr, int length)
{
	_stringB = new stringB;
	_stringB->string_buf = new char[length];
	_stringB->strlen = length;
	for (int i = 0; i < length - 1; i++)
	{
		_stringB->string_buf[i] = ptr[i];
	}
	reflink* rlinking = new reflink;
	rlinking->_address = this;
	rlinking->next = NULL;

	if (_stringB->_reflink == NULL)
	{
		_stringB->_reflink = rlinking;
	}
	else
	{
		reflink* ptr = _stringB->_reflink;
		reflink*  prev = NULL;
		while (ptr)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		prev->next = rlinking;
	}
}

char StringBuffer::charAt(int index) const
{
	if (index <_stringB->strlen)
	{
		return *(_stringB->string_buf + index);
	}
	else {

		throw"\n\n\t##Array Index Out Of Bounds.\n\n";
	}
}


int StringBuffer::length() const {
	// -> returns the length of the buffer
	return _stringB->strlen;
}

void StringBuffer::reserve(int length)
{
	// -> allocates memory of character length size
	_stringB = new stringB;
	_stringB->string_buf = new char[length];
	reflink* rlinking = new reflink;
	rlinking->_address = this;
	rlinking->next = NULL;
	if (_stringB->_reflink == NULL)
	{
		_stringB->_reflink = rlinking;
	}
	else
	{
		reflink* ptr = _stringB->_reflink;
		reflink*  prev = NULL;
		while (ptr)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		prev->next = rlinking;
	}
}

void StringBuffer::append(char c)
{
	// -> appendingcharacter at end of string

	if (_stringB->_refcount>1)
	{
		stringB* str1 = new stringB;
		str1->strlen = _stringB->strlen + 1;
		str1->string_buf = new char[str1->strlen];
		for (int i = 0; i < _stringB->strlen; i++)
		{
			str1->string_buf[i] = _stringB->string_buf[i];
		}
		str1->string_buf[_stringB->strlen] = c;
		_stringB->_refcount--;
		if (_stringB->_reflink->_address == this)
		{
			reflink* str1 = _stringB->_reflink;
			_stringB->_reflink = _stringB->_reflink->next;
			delete str1;
		}
		else {
			reflink* ptr = _stringB->_reflink;
			reflink* prev = NULL;
			while (ptr)
			{
				if (ptr->_address == this)
				{
					prev->next = ptr->next;
					delete ptr;
					break;
				}
				prev = ptr;
				ptr = ptr->next;
			}

		}
		_stringB = str1;
		reflink* rlinking = new reflink;
		rlinking->_address = this;
		rlinking->next = NULL;
		if (_stringB->_reflink == NULL)
		{
			_stringB->_reflink = rlinking;
		}
		else
		{
			reflink* ptr = _stringB->_reflink;
			reflink*  prev = NULL;
			while (ptr)
			{
				prev = ptr;
				ptr = ptr->next;
			}
			prev->next = rlinking;
		}

	}
	else
	{

		char* str1 = _stringB->string_buf;
		_stringB->strlen++;
		_stringB->string_buf = new char[_stringB->strlen];
		for (int i = 0; i < _stringB->strlen - 1; i++)
		{
			_stringB->string_buf[i] = str1[i];
		}
		_stringB->string_buf[_stringB->strlen - 1] = c;
		delete[] str1;

	}


}
reflink* StringBuffer::get_link() {
	return _stringB->_reflink;

}

StringBuffer& StringBuffer::operator = (const StringBuffer& obj)
{
	_stringB = obj._stringB;
	_stringB->_refcount++;
	reflink* rlinking = new reflink;
	rlinking->_address = this;
	rlinking->next = NULL;
	if (_stringB->_reflink == NULL)
	{
		_stringB->_reflink = rlinking;
	}
	else
	{
		reflink* ptr = _stringB->_reflink;
		reflink*  prev = NULL;
		while (ptr)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		prev->next = rlinking;
	}
	return *this;
}

stringB::stringB() 
{
	string_buf = nullptr;
	strlen = 0;
	_refcount = 1;
	_reflink = NULL;
}


