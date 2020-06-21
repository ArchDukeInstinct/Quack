#include "pch.h"
#include "compiler.h"
#include "converter.h"

qck::Compilation::CompilerContext::CompilerContext()
{
	parser = nullptr;
}

qck::Compilation::CompilerContext::~CompilerContext()
{

}

qck::Compilation::CompilerComponent::CompilerComponent(CompilerContext& pContext) :
	context(pContext)
{

}

bool qck::Compilation::CompilerComponent::next()
{
	context.tokenPrev = context.tokenCurr;
	context.tokenCurr = context.parser->getNextToken();

	return context.tokenCurr != Token::Type::None;
}

void qck::Compilation::CompilerComponent::expect()
{
	context.tokenPrev = context.tokenCurr;
	context.tokenCurr = context.parser->getNextToken();

	if (context.tokenCurr == Token::Type::None)
		throw "Unexpected end of input";
}

qck::Token qck::Compilation::CompilerComponent::previous()
{
	return context.tokenPrev;
}

qck::Token qck::Compilation::CompilerComponent::current()
{
	return context.tokenCurr;
}

void qck::Compilation::CompilerComponent::instr(qck::Runtime::Instruction value)
{
	context.listInstruction.insert((int) value);
}

void qck::Compilation::CompilerComponent::instr(int value)
{
	context.listInstruction.insert(value);
}

qck::LinkedStack<int>& qck::Compilation::CompilerComponent::integers()
{
	return context.stackInteger;
}

qck::LinkedStack<std::string>& qck::Compilation::CompilerComponent::strings()
{
	return context.stackString;
}

qck::LinkedStack<qck::Token>& qck::Compilation::CompilerComponent::tokens()
{
	return context.stackToken;
}

int qck::Compilation::CompilerComponent::getInt()
{
	return stringToInt(context.parser->getStringValue());
}

std::string qck::Compilation::CompilerComponent::getString()
{
	return context.parser->getStringValue();
}

qck::Compilation::GlobalCompiler::GlobalCompiler(CompilerContext& pContext, RoutineCompiler& pRoutine, ExpressionCompiler& pExpression)
	: CompilerComponent(pContext), routine(pRoutine), expression(pExpression)
{

}

bool qck::Compilation::GlobalCompiler::operator ()()
{
	if (!next())
		return false;

	if (current().isDataType())
	{
		expect();

		// Store data type for variable / routine
		tokens().push(current());

		if (current().type == Token::Type::Identifier)
		{
			// Store identifier for variable / routine
			strings().push(getString());

			// Branch into variable or routine
			expect();

			switch (current().type)
			{
				case Token::Type::GroupBegin:
					routine();
					break;

				case Token::Type::Assign:
				case Token::Type::LineEnd:

					break;

				default:
					throw "Unexpected token";
			}
		}
	}

	return true;
}

qck::Compilation::RoutineCompiler::RoutineCompiler(CompilerContext& pContext, BlockCompiler& pBlock)
	: CompilerComponent(pContext), block(pBlock)
{

}

void qck::Compilation::RoutineCompiler::operator ()()
{

}

qck::Compilation::BlockCompiler::BlockCompiler(CompilerContext& pContext, StatementCompiler& pStatement)
	: CompilerComponent(pContext), statement(pStatement)
{

}

void qck::Compilation::BlockCompiler::operator ()()
{

}

qck::Compilation::StatementCompiler::StatementCompiler(CompilerContext& pContext, BlockCompiler& pBlock, ExpressionCompiler& pExpression, InvocationCompiler& pInvocation)
	: CompilerComponent(pContext), block(pBlock), expression(pExpression), invocation(pInvocation)
{

}

void qck::Compilation::StatementCompiler::operator ()()
{

}

qck::Compilation::VariableCompiler::VariableCompiler(CompilerContext& pContext, ExpressionCompiler& pExpression)
	: CompilerComponent(pContext), expression(pExpression)
{

}

void qck::Compilation::VariableCompiler::operator ()()
{

}

qck::Compilation::ExpressionCompiler::ExpressionCompiler(CompilerContext& pContext, InvocationCompiler& pInvocation)
	: CompilerComponent(pContext), invocation(pInvocation)
{

}

void qck::Compilation::ExpressionCompiler::operator ()()
{

}

qck::Compilation::InvocationCompiler::InvocationCompiler(CompilerContext& pContext, ExpressionCompiler& pExpression)
	: CompilerComponent(pContext), expression(pExpression)
{

}

void qck::Compilation::InvocationCompiler::operator ()()
{

}

qck::Compiler::Compiler() :
	global(context, routine, expression),
	routine(context, block),
	block(context, statement),
	statement(context, block, expression, invocation),
	expression(context, invocation),
	invocation(context, expression)
{

}

qck::Compiler::~Compiler()
{

}

bool qck::Compiler::compile(Parser* pParser)
{
	context.parser		= pParser;
	context.tokenPrev	= Token::Type::None;
	context.tokenCurr	= Token::Type::None;
	context.tokenNext	= Token::Type::None;
	
	context.stackInteger.clear();
	context.stackString.clear();
	context.listInstruction.clear();

	try
	{
		while (global());
	}
	catch (std::string exception)
	{
		return false;
	}

	return true;
}
