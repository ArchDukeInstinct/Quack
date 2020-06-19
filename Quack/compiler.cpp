#include "pch.h"
#include "compiler.h"

qck::Compilation::CompilerBase::CompilerBase(CompilerContext* pContext)
{
	context = pContext;
}

bool qck::Compilation::CompilerBase::next()
{
	return false;
}

qck::Token qck::Compilation::CompilerBase::current()
{
	return Token::Type::None;
}

qck::Token qck::Compilation::CompilerBase::previous()
{
	return Token::Type::None;
}

int qck::Compilation::CompilerBase::peekInteger()
{
	return 0;
}

void qck::Compilation::CompilerBase::pushInteger()
{

}

int qck::Compilation::CompilerBase::popInteger()
{
	return 0;
}

std::string qck::Compilation::CompilerBase::peekString()
{
	return "";
}

void qck::Compilation::CompilerBase::pushString()
{

}

std::string qck::Compilation::CompilerBase::popString()
{
	return "";
}

qck::Compilation::GlobalCompiler::GlobalCompiler(CompilerContext* pContext, RoutineCompiler& pRoutine)
	: CompilerBase(pContext), routine(pRoutine)
{

}

void qck::Compilation::GlobalCompiler::operator ()()
{

}

qck::Compilation::RoutineCompiler::RoutineCompiler(CompilerContext* pContext, BlockCompiler& pBlock)
	: CompilerBase(pContext), block(pBlock)
{

}

void qck::Compilation::RoutineCompiler::operator ()()
{

}

qck::Compilation::BlockCompiler::BlockCompiler(CompilerContext* pContext, StatementCompiler& pStatement)
	: CompilerBase(pContext), statement(pStatement)
{

}

void qck::Compilation::BlockCompiler::operator ()()
{

}

qck::Compilation::StatementCompiler::StatementCompiler(CompilerContext* pContext, BlockCompiler& pBlock, ExpressionCompiler& pExpression, InvocationCompiler& pInvocation)
	: CompilerBase(pContext), block(pBlock), expression(pExpression), invocation(pInvocation)
{

}

void qck::Compilation::StatementCompiler::operator ()()
{

}

qck::Compilation::ExpressionCompiler::ExpressionCompiler(CompilerContext* pContext, InvocationCompiler& pInvocation)
	: CompilerBase(pContext), invocation(pInvocation)
{

}

void qck::Compilation::ExpressionCompiler::operator ()()
{

}

qck::Compilation::InvocationCompiler::InvocationCompiler(CompilerContext* pContext, ExpressionCompiler& pExpression)
	: CompilerBase(pContext), expression(pExpression)
{

}

void qck::Compilation::InvocationCompiler::operator ()()
{

}

qck::Compiler::Compiler() :
	global(&context, routine),
	routine(&context, block),
	block(&context, statement),
	statement(&context, block, expression, invocation),
	expression(&context, invocation),
	invocation(&context, expression)
{

}

qck::Compiler::~Compiler()
{

}

void qck::Compiler::setParser(Parser*)
{

}

void qck::Compiler::setParser(Parser&)
{

}