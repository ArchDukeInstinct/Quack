#pragma once

namespace qck
{
	enum class Instruction
	{
		Null,

		Int_Push,
		Int_Pop,
		Int_GetLocal,
		Int_SetLocal,
		Int_GetGlobal,
		Int_SetGlobal,
		Int_Addition,
		Int_Subtraction,
		Int_Multiplication,
		Int_Division,
		Int_Modulus,
		Int_To_Str,

		Str_Push,
		Str_Pop,
		Str_GetLocal,
		Str_SetLocal,
		Str_GetGlobal,
		Str_SetGlobal,
		Str_Concatenate,
		Str_GetLength,
		Str_To_Int,

		Condition,
		Goto,
		Break,
		Return,

		Fn_Write,

		Total
	};
}