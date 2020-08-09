#include "pch.h"
#include "parser.h"

qck::Parser::Parser()
{
	buffer		= new char[BUFFER_SIZE];
	token		= new char[TOKEN_SIZE];
	tokenCount	= 0;
	chrPrev		= '\0';
	chrCurr		= '\0';
	tabPrev		= 0;
	tabCurr		= 0;
	position	= -1;
	count		= 0;
	state		= State::LineNext;
	iterations = 0;
}

qck::Parser::~Parser()
{
	delete[] buffer;
	delete[] token;
}

void qck::Parser::next()
{
	chrPrev = chrCurr;

	if (++iterations >= 3000)
	{
		state = State::End;
		return;
	}

	if (++position >= count)
	{
		count = load(buffer, BUFFER_SIZE);

		if (count <= 0)
		{
			state = State::End;
			return;
		}
		else
			position = 0;
	}

	chrCurr = buffer[position];
}

void qck::Parser::push()
{
	if (tokenCount < TOKEN_SIZE)
	{
		token[tokenCount] = chrCurr;
		++tokenCount;
	}

	next();
}

bool qck::Parser::isWhitespace(char chr)
{
	return chr == ' ' || chr == '\t' || chr == '\n';
}

bool qck::Parser::isAlpha(char chr)
{
	return (chr >= 'a' && chr <= 'z') ||
		   (chr >= 'A' && chr <= 'Z');
}

bool qck::Parser::isDigit(char chr)
{
	return chr >= '0' && chr <= '9';
}

bool qck::Parser::isOperator(char chr)
{
	return chr == '!' || chr == '%' || chr == '&' || chr == '*' ||
		   chr == '+' || chr == '-' || chr == '/' || chr == '^' || 
		   chr == '|' || (chr >= '<' && chr <= '?');
}

qck::Token::Type qck::Parser::parseLineNext()
{
	tabCurr = 0;

	while (state == State::LineNext)
	{
		next();

		if (chrCurr == '\t')
			++tabCurr;
		else if (chrCurr == '\n')
			tabCurr = 0;
		else if (chrCurr != ' ')
			break;
	}

	state = State::LineStart;
	return parseLineStart();
}

qck::Token::Type qck::Parser::parseLineStart()
{
	if (tabCurr > tabPrev)
	{
		if (tabCurr > tabPrev + 1)
		{
			state = State::End;
			return Token::Type::Invalid;
		}
		else
		{
			tabPrev = tabCurr;
			return Token::Type::ScopeBegin;
		}
	}
	else if (tabCurr < tabPrev)
	{
		--tabPrev;
		return Token::Type::ScopeEnd;
	}

	state = State::LineMidway;
	return parseGeneral();
}

qck::Token::Type qck::Parser::parseGeneral()
{
	while (state != State::End)
	{
		if (chrCurr == '\n')
			return Token::Type::LineEnd;
		else if (chrCurr == '\'')
			return parseSingleQuote();
		else if (chrCurr == '"')
			return parseDoubleQuote();
		else if (isDigit(chrCurr))
			return parseInteger();
		else if (isAlpha(chrCurr))
			return parseText();
		else if (isOperator(chrCurr))
			return parseOperator();

		next();

		switch (chrPrev)
		{
			case '(': return Token::Type::GroupBegin;
			case ')': return Token::Type::GroupEnd;
			case ',': return Token::Type::GroupNext;
		}
	}

	return Token::Type::Invalid;
}

qck::Token::Type qck::Parser::parseSingleQuote()
{
	next();

	while (state != State::End && chrCurr != '\'')
		push();

	next();

	return chrPrev == '\'' ? Token::Type::StringLiteral : Token::Type::Invalid;
}

qck::Token::Type qck::Parser::parseDoubleQuote()
{
	next();

	while (state != State::End && chrCurr != '"')
		push();

	next();

	return chrPrev == '"' ? Token::Type::StringLiteral : Token::Type::Invalid;
}

qck::Token::Type qck::Parser::parseInteger()
{
	while (state != State::End && isDigit(chrCurr))
		push();

	if (chrCurr == '.')
		return parseFloat();

	return Token::Type::IntegerLiteral;
}

qck::Token::Type qck::Parser::parseFloat()
{
	next();

	while (state != State::End && isDigit(chrCurr))
		push();

	if (chrCurr == '.')
		return Token::Type::Invalid;

	return Token::Type::FloatLiteral;
}

qck::Token::Type qck::Parser::parseText()
{
	while (state != State::End && (isAlpha(chrCurr) || chrCurr == '_'))
		push();

	std::string str(token, tokenCount);
	for (auto it = str.begin(); it != str.end(); ++it)
		if (*it >= 'A' && *it <= 'Z')
			*it = char(*it + 32);

	switch (token[0])
	{
		case 'a':
			if (str == "auto")
				return Token::Type::Auto;
			break;
		case 'b':
			if (str == "bool")
				return Token::Type::Boolean;
			else if (str == "break")
				return Token::Type::Break;
			break;
		case 'c':
			if (str == "class")
				return Token::Type::Class;
			break;
		case 'f':
			if (str == "false")
				return Token::Type::BooleanFalse;
			if (str == "float")
				return Token::Type::Float;
			else if (str == "for")
				return Token::Type::For;
			break;
		case 'i':
			if (str == "if")
				return Token::Type::If;
			else if (str == "int")
				return Token::Type::Integer;
			break;
		case 'r':
			if (str == "return")
				return Token::Type::Return;
			break;
		case 's':
			if (str == "string")
				return Token::Type::String;
			break;
		case 'v':
			if (str == "void")
				return Token::Type::Void;
			break;
		case 't':
			if (str == "true")
				return Token::Type::BooleanTrue;
			break;
		case 'w':
			if (str == "while")
				return Token::Type::While;
			break;
		case 'y':
			if (str == "yield")
				return Token::Type::Yield;
			break;
	}

	return Token::Type::Identifier;
}

qck::Token::Type qck::Parser::parseOperator()
{
	while (state != State::End && isOperator(chrCurr))
		push();

	switch (tokenCount)
	{
		case 1:
			switch (token[0])
			{
				case '!': return Token::Type::Inverse;
				case '=': return Token::Type::Assign;
				case '+': return Token::Type::Addition;
				case '-': return Token::Type::Subtraction;
				case '*': return Token::Type::Multiplication;
				case '/': return Token::Type::Division;
				case '%': return Token::Type::Modulus;
				case '<': return Token::Type::Lesser;
				case '>': return Token::Type::Greater;
			}
			break;

		case 2:
			if (token[0] == token[1])
			{
				switch (token[0])
				{
					case '=': return Token::Type::Equal;
					case '+': return Token::Type::Increment;
					case '-': return Token::Type::Decrement;
					case '*': return Token::Type::Exponent;
					case '&': return Token::Type::AND;
					case '|': return Token::Type::OR;
				}
			}
			else if (token[1] == '=')
			{
				switch (token[0])
				{
					case '!': return Token::Type::Unequal;
					case '+': return Token::Type::Add;
					case '-': return Token::Type::Subtract;
					case '*': return Token::Type::Multiply;
					case '/': return Token::Type::Divide;
					case '%': return Token::Type::Modulo;
					case '<': return Token::Type::LesserOrEqual;
					case '>': return Token::Type::GreaterOrEqual;
				}
			}
			break;

		case 3:
			if (token[1] == '=' && token[2] == '=')
			{
				switch (token[0])
				{
					case '=': return Token::Type::ValueEqual;
					case '!': return Token::Type::ValueUnequal;
				}
			}
			break;
	}

	return Token::Type::Invalid;
}

qck::Token::Type qck::Parser::parseInputEnd()
{
	if (tabPrev > 0)
	{
		--tabPrev;
		return Token::Type::ScopeEnd;
	}

	return Token::Type::None;
}

qck::Token qck::Parser::getNextToken()
{
	Token result;

	tokenCount = 0;

	switch (state)
	{
		case State::LineNext:	result = parseLineNext();	break;
		case State::LineStart:	result = parseLineStart();	break;
		case State::LineMidway: result = parseGeneral();	break;
		case State::End:		result = parseInputEnd();	break;
	}

	if (result == Token::Type::LineEnd)
		state = State::LineNext;

	return result;
}

std::string qck::Parser::getStringValue()
{
	return tokenCount > 0 ? std::string(token, tokenCount) : "";
}

void qck::Parser::reset()
{
	tokenCount	= 0;
	chrPrev		= '\0';
	chrCurr		= '\0';
	tabPrev		= 0;
	tabCurr		= 0;
	position	= -1;
	state		= State::LineNext;
	iterations	= 0;

	count = rewind(buffer, BUFFER_SIZE);
}