#pragma once

#include "pch.h"
#include "token.h"

namespace qck
{
	// ========================================================================================================================================
	// Parser
	// ========================================================================================================================================

	class Parser
	{
		private:

		const int BUFFER_SIZE	= 1024;
		const int TOKEN_SIZE	= 256;

		enum class State
		{
			LineNext,
			LineStart,
			LineMidway,
			End
		};

		State state;
		Token tokenCurr;
		char *buffer, *token;
		char chrPrev, chrCurr;
		int position, count, tokenCount;
		int tabPrev, tabCurr;

		int iterations; // debug

		void next();
		void push();

		bool isWhitespace(char);
		bool isAlpha(char);
		bool isDigit(char);
		bool isOperator(char);

		Token::Type parseLineNext();
		Token::Type parseLineStart();
		Token::Type parseGeneral();
		Token::Type parseSingleQuote();
		Token::Type parseDoubleQuote();
		Token::Type parseInteger();
		Token::Type parseFloat();
		Token::Type parseText();
		Token::Type parseOperator();
		Token::Type parseInputEnd();

		protected:

		virtual int load(char*, int)	= 0;
		virtual int rewind(char*, int)	= 0;

		public:

		Parser();
		virtual ~Parser();

		Token getNextToken();
		std::string getStringValue();

		void reset();
	};
}