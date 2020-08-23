#pragma once

namespace qck::Runtime
{
	/*
		Enum to functions

		Regex:		(?:(?:\s*)|(?:\/\/.+))*([a-zA-Z]+)(?: = 0)?,
		Replace:	void instr$1\(\)\n{\n\n}\n\n

		Enum to function pointer array

		Regex:		(?:(?:\s*)|(?:\/\/.+))*([a-zA-Z]+)(?: = 0)?,
		Replace:	instructions\[(unsigned int) Instruction::$1\] = instr$1;\n
	*/

	enum class Instruction
	{
		Null = 0,

		// Integer
		IntPush,
		IntPop,
		IntGetLocal,
		IntSetLocal,
		IntGetGlobal,
		IntSetGlobal,
		IntAddition,
		IntSubtraction,
		IntMultiplication,
		IntDivision,
		IntModulus,
		IntToStr,

		// String
		StrPush,
		StrPop,
		StrGetLocal,
		StrSetLocal,
		StrGetGlobal,
		StrSetGlobal,
		StrConcatenate,
		StrGetLength,
		StrToInt,

		// Control
		Condition,
		Goto,
		Return,

		// Builtin
		FnWrite,

		Total
	};

	//extern void instrInit();
	//extern void instrRun(int*, int);
}