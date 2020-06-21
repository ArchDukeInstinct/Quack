#include "pch.h"
#include "stack.h"

qck::Runtime::Stack::Stack()
{
	data	= new unsigned char[STACK_SIZE];
	offset	= 0;
}

qck::Runtime::Stack::~Stack()
{
	if (data != nullptr)
		delete[] data;
}

int qck::Runtime::Stack::intPush(int value)
{
	return 0;
}

int qck::Runtime::Stack::intPop()
{
	return 0;
}

int qck::Runtime::Stack::intPeek()
{
	return 0;
}

int qck::Runtime::Stack::strPush(const std::string& value)
{
	return 0;
}

std::string qck::Runtime::Stack::strPop()
{
	return "";
}

std::string qck::Runtime::Stack::strPeek()
{
	return "";
}