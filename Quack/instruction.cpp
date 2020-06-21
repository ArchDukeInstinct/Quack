#include "pch.h"
#include "instruction.h"

typedef void (*Instr)();

Instr instructions[(unsigned int) qck::Runtime::Instruction::Total];

void instrNull()
{
	// do nothing
}

void instrIntPush()
{

}

void instrIntPop()
{

}

void instrIntGetLocal()
{

}

void instrIntSetLocal()
{

}

void instrIntGetGlobal()
{

}

void instrIntSetGlobal()
{

}

void instrIntAddition()
{

}

void instrIntSubtraction()
{

}

void instrIntMultiplication()
{

}

void instrIntDivision()
{

}

void instrIntModulus()
{

}

void instrIntToStr()
{

}

void instrStrPush()
{

}

void instrStrPop()
{

}

void instrStrGetLocal()
{

}

void instrStrSetLocal()
{

}

void instrStrGetGlobal()
{

}

void instrStrSetGlobal()
{

}

void instrStrConcatenate()
{

}

void instrStrGetLength()
{

}

void instrStrToInt()
{

}

void instrCondition()
{

}

void instrGoto()
{

}

void instrBreak()
{

}

void instrReturn()
{

}

void instrFnWrite()
{

}

void qck::Runtime::instrInit()
{
	using qck::Runtime::Instruction;

	static bool init = false;
	if (init)
		return;
	init = true;

	instructions[(unsigned int) Instruction::Null]				= &instrNull;
	instructions[(unsigned int) Instruction::IntPush]			= &instrIntPush;
	instructions[(unsigned int) Instruction::IntPop]			= &instrIntPop;
	instructions[(unsigned int) Instruction::IntGetLocal]		= &instrIntGetLocal;
	instructions[(unsigned int) Instruction::IntSetLocal]		= &instrIntSetLocal;
	instructions[(unsigned int) Instruction::IntGetGlobal]		= &instrIntGetGlobal;
	instructions[(unsigned int) Instruction::IntSetGlobal]		= &instrIntSetGlobal;
	instructions[(unsigned int) Instruction::IntAddition]		= &instrIntAddition;
	instructions[(unsigned int) Instruction::IntSubtraction]	= &instrIntSubtraction;
	instructions[(unsigned int) Instruction::IntMultiplication]	= &instrIntMultiplication;
	instructions[(unsigned int) Instruction::IntDivision]		= &instrIntDivision;
	instructions[(unsigned int) Instruction::IntModulus]		= &instrIntModulus;
	instructions[(unsigned int) Instruction::IntToStr]			= &instrIntToStr;
	instructions[(unsigned int) Instruction::StrPush]			= &instrStrPush;
	instructions[(unsigned int) Instruction::StrPop]			= &instrStrPop;
	instructions[(unsigned int) Instruction::StrGetLocal]		= &instrStrGetLocal;
	instructions[(unsigned int) Instruction::StrSetLocal]		= &instrStrSetLocal;
	instructions[(unsigned int) Instruction::StrGetGlobal]		= &instrStrGetGlobal;
	instructions[(unsigned int) Instruction::StrSetGlobal]		= &instrStrSetGlobal;
	instructions[(unsigned int) Instruction::StrConcatenate]	= &instrStrConcatenate;
	instructions[(unsigned int) Instruction::StrGetLength]		= &instrStrGetLength;
	instructions[(unsigned int) Instruction::StrToInt]			= &instrStrToInt;
	instructions[(unsigned int) Instruction::Condition]			= &instrCondition;
	instructions[(unsigned int) Instruction::Goto]				= &instrGoto;
	instructions[(unsigned int) Instruction::Break]				= &instrBreak;
	instructions[(unsigned int) Instruction::Return]			= &instrReturn;
	instructions[(unsigned int) Instruction::FnWrite]			= &instrFnWrite;
}

void qck::Runtime::instrRun(int* list, int size)
{

}