#pragma once

#include "pch.h"
#include "signature.h"
#include "data.h"

namespace qck
{
	class Compiler;
	class Interpreter;

	// ========================================================================================================================================
	// Context
	// ========================================================================================================================================

	class Context
	{
		friend Compiler;
		friend Interpreter;

		private:

		std::vector<Global> globals;
		std::vector<Routine> routines;

		public:

		Context();
	};
}