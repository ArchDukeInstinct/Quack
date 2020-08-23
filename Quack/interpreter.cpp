#include "pch.h"
#include "interpreter.h"

void outputEmpty(const std::string&)
{

}

qck::Runtime::Interpreter::Interpreter()
{
	output = outputEmpty;

	instructions[(unsigned int) Instruction::Null]				= &Interpreter::instrNull;
	instructions[(unsigned int) Instruction::IntPush]			= &Interpreter::instrIntPush;
	instructions[(unsigned int) Instruction::IntPop]			= &Interpreter::instrIntPop;
	instructions[(unsigned int) Instruction::IntGetLocal]		= &Interpreter::instrIntGetLocal;
	instructions[(unsigned int) Instruction::IntSetLocal]		= &Interpreter::instrIntSetLocal;
	instructions[(unsigned int) Instruction::IntGetGlobal]		= &Interpreter::instrIntGetGlobal;
	instructions[(unsigned int) Instruction::IntSetGlobal]		= &Interpreter::instrIntSetGlobal;
	instructions[(unsigned int) Instruction::IntAddition]		= &Interpreter::instrIntAddition;
	instructions[(unsigned int) Instruction::IntSubtraction]	= &Interpreter::instrIntSubtraction;
	instructions[(unsigned int) Instruction::IntMultiplication]	= &Interpreter::instrIntMultiplication;
	instructions[(unsigned int) Instruction::IntDivision]		= &Interpreter::instrIntDivision;
	instructions[(unsigned int) Instruction::IntModulus]		= &Interpreter::instrIntModulus;
	instructions[(unsigned int) Instruction::IntToStr]			= &Interpreter::instrIntToStr;
	instructions[(unsigned int) Instruction::StrPush]			= &Interpreter::instrStrPush;
	instructions[(unsigned int) Instruction::StrPop]			= &Interpreter::instrStrPop;
	instructions[(unsigned int) Instruction::StrGetLocal]		= &Interpreter::instrStrGetLocal;
	instructions[(unsigned int) Instruction::StrSetLocal]		= &Interpreter::instrStrSetLocal;
	instructions[(unsigned int) Instruction::StrGetGlobal]		= &Interpreter::instrStrGetGlobal;
	instructions[(unsigned int) Instruction::StrSetGlobal]		= &Interpreter::instrStrSetGlobal;
	instructions[(unsigned int) Instruction::StrConcatenate]	= &Interpreter::instrStrConcatenate;
	instructions[(unsigned int) Instruction::StrGetLength]		= &Interpreter::instrStrGetLength;
	instructions[(unsigned int) Instruction::StrToInt]			= &Interpreter::instrStrToInt;
	instructions[(unsigned int) Instruction::Condition]			= &Interpreter::instrCondition;
	instructions[(unsigned int) Instruction::Goto]				= &Interpreter::instrGoto;
	instructions[(unsigned int) Instruction::Return]			= &Interpreter::instrReturn;
	instructions[(unsigned int) Instruction::FnWrite]			= &Interpreter::instrFnWrite;
}

qck::Runtime::Interpreter::~Interpreter()
{

}

bool qck::Runtime::Interpreter::load(char* data, int dataSize)
{
	const int start = 8;

	std::string version = "0000";
	int *list, size;

	// Check for valid header
	if (dataSize < start || !(data[0] == 'Q' && data[1] == 'C' && data[2] == 'K') || std::string(data[3], 4) != version)
		return false;

	// Clear existing data
	for (auto routine : routines)
		delete[] routine.instrList;

	routines.clear();

	// Load new data
	for (int i = start, j, k; i < dataSize; ++i)
	{
		size = data[i];
		list = new int[size];

		j = i + size;
		if (j < dataSize)
			return false;

		for (k = 0; i < j; ++i, ++k)
			list[k] = data[i];

		routines.push_back(Routine());

		auto routine		= routines.at(routines.size() - 1);
		routine.instrList	= list;
		routine.instrSize	= size;
	}

	return true;
}

void qck::Runtime::Interpreter::invokeRoutine(size_t id)
{
	if (id < 0 || id >= routines.size())
		throw "Routine does not exist";

	auto routine = routines.at(id);

	run(routine.instrList, routine.instrSize);
}

void qck::Runtime::Interpreter::invokeRoutine(std::string identifier)
{
	auto id = routineMap.find(identifier);
	if (id == routineMap.end())
		throw "Routine does not exist";

	auto routine = routines.at(id->second);
	run(routine.instrList, routine.instrSize);
}

void qck::Runtime::Interpreter::setOutput(OutputFn pOutput)
{
	output = pOutput;
}

void qck::Runtime::Interpreter::run(int* list, int size)
{
	instrList = list;
	instrSize = size;
	instrCurr = -1;

	while (instrCurr < instrSize)
	{
		std::invoke(instructions[instrList[++instrCurr]], this);
	}
}

void qck::Runtime::Interpreter::instrNull()
{
	// do nothing
}

void qck::Runtime::Interpreter::instrIntPush()
{
	stack.push<int>(instrList[++instrCurr]);
}

void qck::Runtime::Interpreter::instrIntPop()
{
	stack.pop<int>();
}

void qck::Runtime::Interpreter::instrIntGetLocal()
{
	int offset = instrList[++instrCurr];
	stack.push<int>(*stack.get<int>(offset));
}

void qck::Runtime::Interpreter::instrIntSetLocal()
{
	int offset = instrList[++instrCurr];
	*stack.get<int>(offset) = *stack.peek<int>();
}

void qck::Runtime::Interpreter::instrIntGetGlobal()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrIntSetGlobal()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrIntAddition()
{
	int a, b;

	stack.pop(b);
	stack.pop(a);
	stack.push(a + b);
}

void qck::Runtime::Interpreter::instrIntSubtraction()
{
	int a, b;

	stack.pop(b);
	stack.pop(a);
	stack.push(a - b);
}

void qck::Runtime::Interpreter::instrIntMultiplication()
{
	int a, b;

	stack.pop(b);
	stack.pop(a);
	stack.push(a * b);
}

void qck::Runtime::Interpreter::instrIntDivision()
{
	int a, b;

	stack.pop(b);
	stack.pop(a);
	stack.push(a / b);
}

void qck::Runtime::Interpreter::instrIntModulus()
{
	int a, b;

	stack.pop(b);
	stack.pop(a);
	stack.push(a % b);
}

void qck::Runtime::Interpreter::instrIntToStr()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrStrPush()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrStrPop()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrStrGetLocal()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrStrSetLocal()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrStrGetGlobal()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrStrSetGlobal()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrStrConcatenate()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrStrGetLength()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrStrToInt()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrCondition()
{
	int value;

	stack.pop(value);
	++instrCurr;

	if (!value)
		instrCurr = instrList[instrCurr];
	else
		++instrCurr;
}

void qck::Runtime::Interpreter::instrGoto()
{
	instrCurr = instrList[++instrCurr];
}

void qck::Runtime::Interpreter::instrReturn()
{
	throw "Instruction not implemented";
}

void qck::Runtime::Interpreter::instrFnWrite()
{
	std::string text;

	stack.pop(text);
	output(text);
}

void qck::Runtime::Interpreter::instrFnRandom()
{
	int min = instrList[++instrCurr];
	int max = instrList[++instrCurr];

	stack.push<int>(min + rand() % (max - min));
}
