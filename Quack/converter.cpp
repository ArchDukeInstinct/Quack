#include "pch.h"
#include "converter.h"

std::stringstream ss;

int qck::stringToInt(const std::string& value)
{
	int result;

	ss.clear();
	ss.str(value);
	ss >> result;

	return result;
}

bool qck::stringToInt(const std::string& value, int& result)
{
	ss.clear();
	ss.str(value);
	ss >> result;

	return ss.good();
}