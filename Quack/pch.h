#pragma once

#include <cstdint>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <initializer_list>

#ifdef _DEBUG

	#define qckAssert(condition, message) \
		if (!(condition)) \
			throw message

#else

	#define qckAssert(condition, message)

#endif