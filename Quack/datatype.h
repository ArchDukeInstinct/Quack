#pragma once

namespace qck
{
	enum class DataType
	{
		None,
		Void,
		Boolean,
		Integer,
		Float,
		String,
		Auto
	};

	const std::string DataTypeText[] =
	{
		"",
		"void",
		"bool",
		"int",
		"float",
		"string",
		"auto"
	};
}