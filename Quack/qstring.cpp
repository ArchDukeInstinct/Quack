#include "pch.h"
#include "qstring.h"

qck::Runtime::QString::QString() :
	buffer(nullptr), capacity(0), size(0)
{

}

qck::Runtime::QString::~QString()
{
	if (buffer != nullptr)
		delete[] buffer;
}

int qck::Runtime::QString::getLength() const
{
	return size;
}

void qck::Runtime::QString::resize(size_t required)
{
	char* o = buffer;

	capacity	= std::pow(2, std::ceil(std::log2(required)));
	buffer		= new char[capacity];

	if (o != nullptr)
	{
		int s = size < capacity ? size : capacity;

		for (int i = 0; i < s; ++i)
			buffer[i] = o[i];

		delete[] o;
	}
}

int qck::Runtime::QString::indexOf(char chr) const
{
	for (auto i = 0; i < size; ++i)
		if (buffer[i] == chr)
			return i;

	return -1;
}

int qck::Runtime::QString::indexOf(QString* qstr) const
{
	char* str = qstr->buffer;
	int i, j, s = qstr->size;

	for (i = 0, j = 0; i < size; ++i)
	{
		if (buffer[i] == str[j])
		{
			if (++j == s)
				return i - s;
		}
		else
			j = 0;
	}
}

void qck::Runtime::QString::append(char chr)
{
	if (size + 1 > capacity)
		resize(capacity << 1);

	buffer[size] = chr;
	++size;
}

void qck::Runtime::QString::append(QString* qstr)
{
	char* str	= qstr->buffer;
	int length	= qstr->size;

	if (size + length > capacity)
		resize(size + length);

	for (int i = 0; i < length; ++i)
		buffer[size + i] = str[i];

	size += length;
}

void qck::Runtime::QString::append(int* instr, int length)
{
	while (--length >= 0)
	{
		buffer[size] = (char) *instr;

		++instr;
		++size;
	}
}

void qck::Runtime::QString::append(int value)
{
	ss.clear();
	ss << value;

	int length = ss.gcount();
	if (size + length > capacity)
		resize(size + length);

	ss.get(buffer + size, length);
}

void qck::Runtime::QString::clear()
{
	size = 0;
}

void qck::Runtime::QString::concatenate(const QString* a, const QString* b, QString* result)
{
	size_t total = a->size + b->size;
	char *buffer = result->buffer, *str;
	int i, j = 0, s;

	if (result->capacity < total)
		result->resize(total);

	str = a->buffer;
	for (i = 0, s = a->size; i < s; ++i, ++j)
		buffer[j] = str[i];

	str = b->buffer;
	for (i = 0, s = b->size; i < s; ++i, ++j)
		buffer[j] = str[i];

	result->size = total;
}

void qck::Runtime::QString::swap(QString* src, QString* dst)
{
	char* ptr = dst->buffer;

	dst->buffer = src->buffer;
	src->buffer = ptr;
}