#pragma once

#include "pch.h"
#include "token.h"
#include "parser.h"
#include "list.h"
#include "stack.h"
#include "instruction.h"

namespace qck::Compilation
{
	class GlobalCompiler;
	class RoutineCompiler;
	class BlockCompiler;
	class StatementCompiler;
	class ExpressionCompiler;
	class InvocationCompiler;

	// ========================================================================================================================================
	// CompilerContext
	// ========================================================================================================================================

	class CompilerContext
	{
		public:

		Parser* parser;
		Token tokenPrev;
		Token tokenCurr;

		List<uint8_t> instructions;
	};

	// ========================================================================================================================================
	// CompilerBase
	// ========================================================================================================================================

	class CompilerBase
	{
		private:

		CompilerContext* context;

		protected:

		bool next();
		Token current();
		Token previous();

		int peekInteger();
		void pushInteger();
		int popInteger();

		std::string peekString();
		void pushString();
		std::string popString();

		public:

		CompilerBase(CompilerContext*);
	};

	// ========================================================================================================================================
	// GlobalCompiler
	// ========================================================================================================================================

	class GlobalCompiler : public CompilerBase
	{
		RoutineCompiler& routine;

		public:

		GlobalCompiler(CompilerContext*, RoutineCompiler&);

		void operator ()();
	};

	// ========================================================================================================================================
	// RoutineCompiler
	// ========================================================================================================================================

	class RoutineCompiler : public CompilerBase
	{
		private:
		
		BlockCompiler& block;

		public:

		RoutineCompiler(CompilerContext*, BlockCompiler&);

		void operator ()();
	};

	// ========================================================================================================================================
	// BlockCompiler
	// ========================================================================================================================================

	class BlockCompiler : public CompilerBase
	{
		private:

		StatementCompiler& statement;

		public:

		BlockCompiler(CompilerContext*, StatementCompiler&);

		void operator ()();
	};

	// ========================================================================================================================================
	// StatementCompiler
	// ========================================================================================================================================

	class StatementCompiler : public CompilerBase
	{
		private:

		BlockCompiler& block;
		ExpressionCompiler& expression;
		InvocationCompiler& invocation;

		public:

		StatementCompiler(CompilerContext*, BlockCompiler&, ExpressionCompiler&, InvocationCompiler&);

		void operator ()();
	};

	// ========================================================================================================================================
	// ExpressionCompiler
	// ========================================================================================================================================

	class ExpressionCompiler : public CompilerBase
	{
		private:

		InvocationCompiler& invocation;

		public:

		ExpressionCompiler(CompilerContext*, InvocationCompiler&);

		void operator ()();
	};

	// ========================================================================================================================================
	// InvocationCompiler
	// ========================================================================================================================================

	class InvocationCompiler : public CompilerBase
	{
		private:

		ExpressionCompiler& expression;

		public:

		InvocationCompiler(CompilerContext*, ExpressionCompiler&);

		void operator ()();
	};
}

namespace qck
{
	class Compiler
	{
		private:

		Compilation::CompilerContext context;
		Compilation::GlobalCompiler global;
		Compilation::RoutineCompiler routine;
		Compilation::BlockCompiler block;
		Compilation::StatementCompiler statement;
		Compilation::ExpressionCompiler expression;
		Compilation::InvocationCompiler invocation;

		public:

		Compiler();
		~Compiler();

		void setParser(Parser*);
		void setParser(Parser&);
	};
}