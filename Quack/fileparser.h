#pragma once

#include "pch.h"
#include "parser.h"

namespace qck
{
	// ========================================================================================================================================
	// FileParser
	// ========================================================================================================================================

	class FileParser : public Parser
	{
		private:

		std::ifstream file;

		protected:

		int load(char*, int);
		int rewind(char*, int);

		public:

		FileParser();
		FileParser(const std::string&);
		~FileParser();

		bool open(const std::string&);
		void close();
	};
}