#pragma once

#include "pch.h"

namespace qck::Runtime
{
	// ========================================================================================================================================
	// Stack
	// ========================================================================================================================================

	class Stack
	{
		private:

		const int STACK_SIZE = 512;

		unsigned char* data;
		size_t offset;

		public:

		Stack();
		~Stack();

		int intPush(int);
		int intPop();
		int intPeek();

		int strPush(const std::string&);
		std::string strPop();
		std::string strPeek();
	};
}