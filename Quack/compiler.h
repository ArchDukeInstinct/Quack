#pragma once

#include "pch.h"
#include "token.h"
#include "parser.h"
#include "list.h"
#include "linkedstack.h"
#include "instruction.h"

namespace qck::Compilation
{
	class GlobalCompiler;
	class RoutineCompiler;
	class BlockCompiler;
	class StatementCompiler;
	class VariableCompiler;
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
		Token tokenNext;

		LinkedStack<int> stackInteger;
		LinkedStack<std::string> stackString;
		LinkedStack<Token> stackToken;

		List<int> listInstruction;

		CompilerContext();
		~CompilerContext();
	};

	// ========================================================================================================================================
	// CompilerComponent
	// ========================================================================================================================================

	class CompilerComponent
	{
		private:

		CompilerContext& context;

		protected:

		bool next();
		void expect();
		Token previous();
		Token current();

		// Instruction
		void instr(qck::Runtime::Instruction);
		void instr(int);

		// Stacks
		LinkedStack<int>& integers();
		LinkedStack<std::string>& strings();
		LinkedStack<Token>& tokens();

		// Value
		int getInt();
		std::string getString();

		public:

		CompilerComponent(CompilerContext&);
	};

	// ========================================================================================================================================
	// GlobalCompiler
	// ========================================================================================================================================

	class GlobalCompiler : public CompilerComponent
	{
		RoutineCompiler& routine;
		ExpressionCompiler& expression;

		public:

		GlobalCompiler(CompilerContext&, RoutineCompiler&, ExpressionCompiler&);

		bool operator ()();
	};

	// ========================================================================================================================================
	// RoutineCompiler
	// ========================================================================================================================================

	class RoutineCompiler : public CompilerComponent
	{
		private:
		
		BlockCompiler& block;

		public:

		RoutineCompiler(CompilerContext&, BlockCompiler&);

		void operator ()();
	};

	// ========================================================================================================================================
	// BlockCompiler
	// ========================================================================================================================================

	class BlockCompiler : public CompilerComponent
	{
		private:

		StatementCompiler& statement;

		public:

		BlockCompiler(CompilerContext&, StatementCompiler&);

		void operator ()();
	};

	// ========================================================================================================================================
	// StatementCompiler
	// ========================================================================================================================================

	class StatementCompiler : public CompilerComponent
	{
		private:

		BlockCompiler& block;
		ExpressionCompiler& expression;
		InvocationCompiler& invocation;

		public:

		StatementCompiler(CompilerContext&, BlockCompiler&, ExpressionCompiler&, InvocationCompiler&);

		void operator ()();
	};

	// ========================================================================================================================================
	// VariableCompiler
	// =======================================================================================================================================

	class VariableCompiler : public CompilerComponent
	{
		private:

		ExpressionCompiler& expression;

		public:

		VariableCompiler(CompilerContext&, ExpressionCompiler&);

		void operator ()();
	};

	// ========================================================================================================================================
	// ExpressionCompiler
	// ========================================================================================================================================

	class ExpressionCompiler : public CompilerComponent
	{
		private:

		InvocationCompiler& invocation;

		public:

		ExpressionCompiler(CompilerContext&, InvocationCompiler&);

		void operator ()();
	};

	// ========================================================================================================================================
	// InvocationCompiler
	// ========================================================================================================================================

	class InvocationCompiler : public CompilerComponent
	{
		private:

		ExpressionCompiler& expression;

		public:

		InvocationCompiler(CompilerContext&, ExpressionCompiler&);

		void operator ()();
	};
}

namespace qck
{
	// ========================================================================================================================================
	// Compiler
	// ========================================================================================================================================

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

		// ====================================================================================================================================
		// Constructor / Destructor
		// ====================================================================================================================================

		Compiler();
		~Compiler();

		// ====================================================================================================================================
		// Compile
		// ====================================================================================================================================

		bool compile(Parser*);
	};
}