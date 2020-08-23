#pragma once

#include "pch.h"
#include "instruction.h"
#include "datatype.h"
#include "stack.h"

namespace qck::Runtime
{
	// ========================================================================================================================================
	// Interpreter
	// ========================================================================================================================================

	class Interpreter
	{
		public:

		typedef void (*OutputFn)(const std::string&);

		private:

		struct Global
		{
			DataType type;
		};

		struct Routine
		{
			int* instrList;
			int instrSize;
		};

		Stack stack;

		std::vector<Global> globals;
		std::vector<Routine> routines;
		std::unordered_map<std::string, size_t> routineMap;

		OutputFn output;

		/* Instructions */
		typedef void (Interpreter::*Instr)();

		Instr instructions[(unsigned int) Instruction::Total];
		int *instrList, instrSize, instrCurr;

		void run(int*, int);

		/* Null */
		void instrNull();

		/* Integer */
		void instrIntPush();
		void instrIntPop();
		void instrIntGetLocal();
		void instrIntSetLocal();
		void instrIntGetGlobal();
		void instrIntSetGlobal();
		void instrIntAddition();
		void instrIntSubtraction();
		void instrIntMultiplication();
		void instrIntDivision();
		void instrIntModulus();
		void instrIntToStr();

		/* String */
		void instrStrPush();
		void instrStrPop();
		void instrStrGetLocal();
		void instrStrSetLocal();
		void instrStrGetGlobal();
		void instrStrSetGlobal();
		void instrStrConcatenate();
		void instrStrGetLength();
		void instrStrToInt();

		/* Control */
		void instrCondition();
		void instrGoto();
		void instrReturn();

		/* Builtins */
		void instrFnWrite();
		void instrFnRandom();

		public:

		/* Constructor / Destructor */
		Interpreter();
		~Interpreter();

		/* Load */
		bool load(char*, int);

		/* Invoke */
		void invokeRoutine(size_t);
		void invokeRoutine(std::string);

		/* Output */
		void setOutput(OutputFn);
	};
}