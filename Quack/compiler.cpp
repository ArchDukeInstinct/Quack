#include "pch.h"
#include "compiler.h"
#include "converter.h"

void qck::Compilation::Writer::write(Runtime::Instruction value)
{
	instructions.push_back((int) value);
}

void qck::Compilation::Writer::write(bool value)
{
	instructions.push_back(value == true);
}

void qck::Compilation::Writer::write(int value)
{
	instructions.push_back(value);
}

void qck::Compilation::Writer::write(const std::string& value)
{
	instructions.push_back((int) value.size());
	for (auto c : value)
		instructions.push_back((int) c);
}

void qck::Compilation::Writer::copyTo(int*& data, int& count)
{
	int size = instructions.size();

	count	= size;
	data	= new int[size];

	for (int i = 0; i < size; ++i)
		data[i] = instructions[i];
}

void qck::Compilation::Writer::clear()
{
	instructions.clear();
}

qck::Compilation::Writer& qck::Compilation::Writer::operator <<(Runtime::Instruction value)
{
	write(value);
	return *this;
}

qck::Compilation::Writer& qck::Compilation::Writer::operator <<(bool value)
{
	write(value);
	return *this;
}

qck::Compilation::Writer& qck::Compilation::Writer::operator <<(int value)
{
	write(value);
	return *this;
}

qck::Compilation::Writer& qck::Compilation::Writer::operator <<(const std::string& value)
{
	write(value);
	return *this;
}

qck::Compilation::Writer& qck::Compilation::Writer::operator >>(Routine& routine)
{
	copyTo(routine.instrList, routine.instrCount);
	return *this;
}

qck::Compilation::TokenIterator::TokenIterator()
{
	parser		= nullptr;
	tokenCurr	= Token::Type::None;
	tokenPrev	= Token::Type::None;
	scope		= 0;
}

bool qck::Compilation::TokenIterator::next()
{
	tokenPrev = tokenCurr;
	tokenCurr = parser->getNextToken();

	switch (tokenCurr.type)
	{
		case Token::Type::None:
			return false;

		case Token::Type::ScopeBegin:
			++scope;
			break;

		case Token::Type::ScopeEnd:
			--scope;
			break;

		case Token::Type::Invalid:
			throw "Encountered invalid token";
	}

	return true;
}

void qck::Compilation::TokenIterator::expect()
{
	if (!next())
		throw "Unexpected end of input";
}

void qck::Compilation::TokenIterator::expect(Token::Type type)
{
	if (!next())
		throw "Unexpected end of input";

	if (tokenCurr != type)
		throw "Expected token '" + Token(type).toString() + "', not '" + tokenCurr.toString() + "'";
}

void qck::Compilation::TokenIterator::expect(Token::Category category)
{
	if (!next())
		throw "Unexpected end of input";

	if (!tokenCurr.is(category))
		throw "Token '" + tokenCurr.toString() + "' was unexpected";
}

void qck::Compilation::TokenIterator::escape()
{
	int current = scope;
	while (next() && scope >= current);
}

void qck::Compilation::Stack::typePush(DataType value)
{
	types.push_front(value);
}

qck::DataType qck::Compilation::Stack::typePop()
{
	qckAssert(!types.empty(), "String stack is empty");

	auto result = *types.begin();
	types.pop_front();

	return result;
}

qck::DataType qck::Compilation::Stack::typePeek()
{
	qckAssert(!types.empty(), "String stack is empty");

	return *types.begin();
}

void qck::Compilation::Stack::intPush(int value)
{
	integers.push_front(value);
}

int qck::Compilation::Stack::intPop()
{
	qckAssert(!integers.empty(), "Integer stack is empty");

	auto result = *integers.begin();
	integers.pop_front();

	return result;
}

int qck::Compilation::Stack::intPeek()
{
	qckAssert(!integers.empty(), "Integer stack is empty");

	return *integers.begin();
}

void qck::Compilation::Stack::strPush(const std::string& value)
{
	strings.push_front(value);
}

std::string qck::Compilation::Stack::strPop()
{
	qckAssert(!integers.empty(), "String stack is empty");

	auto result = *strings.begin();
	strings.pop_front();

	return result;
}

std::string qck::Compilation::Stack::strPeek()
{
	qckAssert(!integers.empty(), "String stack is empty");

	return *strings.begin();
}

void qck::Compiler::typePush()
{
	if (tokenCurr.is(Token::Category::DataType))
		types.push_front(tokenCurr.toType());
	else
		throw "Token is not a data type";
}

void qck::Compiler::intPush()
{
	int value;

	if (stringToInt(parser->getStringValue(), value))
		integers.push_front(value);
	else
		throw "Token is not integer";
}

void qck::Compiler::strPush()
{
	strings.push_front(parser->getStringValue());
}

qck::Compiler::Compiler()
{
	context = nullptr;
}

qck::Compiler::~Compiler()
{

}

void qck::Compiler::readSignature()
{
	if (tokenCurr.is(Token::Category::DataType))
	{
		signature.dataType = tokenCurr.toType();

		expect(Token::Type::Identifier);
		signature.identifier = parser->getStringValue();
	}
	else if (tokenCurr == Token::Type::Identifier)
	{
		signature.dataType		= DataType::None;
		signature.identifier	= parser->getStringValue();
	}

	expect();

	if (tokenCurr == Token::Type::GroupBegin)
	{
		next();

		while (tokenCurr.is(Token::Category::DataType))
		{
			signature.parameters.push_back(tokenCurr.toType());
			expect(Token::Type::Identifier);

			expect();

			if (tokenCurr == Token::Type::GroupNext)
				expect();
		}

		if (tokenCurr != Token::Type::GroupEnd)
			throw "Expected ')'";
	}
}

void qck::Compiler::prelink()
{
	while (next())
	{
		if (tokenCurr.is(Token::Category::DataType))
		{
			readSignature();

			if (tokenCurr == Token::Type::GroupEnd)
			{
				expect(Token::Type::LineEnd);
				expect(Token::Type::ScopeBegin);
				escape();

				signatures.insert(signature, Compilation::Signature::Type::RoutineGlobal, context->routines.size());
				context->routines.push_back(Routine());
			}
			else if (tokenCurr == Token::Type::Assign || tokenCurr == Token::Type::LineEnd)
			{
				throw "Global variables are not implemented yet";
			}
		}
	}
}

void qck::Compiler::expression()
{

}

void qck::Compiler::variable()
{

}

void qck::Compiler::routine()
{

}

void qck::Compiler::build()
{
	const Compilation::SignatureObject* obj;

	while (next())
	{
		if (tokenCurr.is(Token::Category::DataType))
		{
			readSignature();

			obj = signatures.search(signature);

			if (obj == nullptr)
				throw "Signature does not exist";
		}
	}
}

bool qck::Compiler::compile(Parser* pParser)
{
	parser = pParser;

	try
	{
		prelink();
	}
	catch (const char*)
	{
		return false;
	}

	parser->reset();

	try
	{
		build();
	}
	catch (const char*)
	{
		return false;
	}

	return true;
}