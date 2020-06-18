#include "pch.h"
#include "fileparser.h"

qck::FileParser::FileParser()
{

}

qck::FileParser::FileParser(const std::string& filename)
{
	open(filename);
}

qck::FileParser::~FileParser()
{
	close();
}

int qck::FileParser::load(char* buffer, int size)
{
	if (!file.is_open() || !file.good())
		return 0;

	file.read(buffer, size);

	return !file.bad() ? (int) file.gcount() : 0;
}

int qck::FileParser::rewind(char* buffer, int size)
{
	if (!file.is_open() || !file.good())
		return 0;

	file.seekg(0, file.beg);
	file.read(buffer, size);

	return !file.bad() ? (int) file.gcount() : 0;
}

bool qck::FileParser::open(const std::string& filename)
{
	if (file.is_open())
		file.close();

	file.open(filename);

	return file.is_open();
}

void qck::FileParser::close()
{
	if (file.is_open())
		file.close();
}