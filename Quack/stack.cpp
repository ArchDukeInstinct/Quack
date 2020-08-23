#include "pch.h"
#include "stack.h"

qck::Runtime::Stack::Stack()
{
	buffer = new byte[STACK_SIZE];
	offset = 0;
}

qck::Runtime::Stack::~Stack()
{
	if (buffer != nullptr)
		delete[] buffer;
}

size_t qck::Runtime::Stack::getOffset()
{
	return offset;
}