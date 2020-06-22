#pragma once

#include "datatype.h"

namespace qck
{
	// ========================================================================================================================================
	// Token
	// ========================================================================================================================================

	class Token
	{
		public:

		// ====================================================================================================================================
		// Type
		// ====================================================================================================================================

		enum class Type
		{
			None = 0,
			Invalid,

			// Syntax
			ScopeBegin,
			ScopeEnd,
			GroupBegin,
			GroupNext,
			GroupEnd,
			LineEnd,

			// Data Types
			Void,
			Boolean,
			Integer,
			Float,
			String,
			Auto,

			// Term
			BooleanFalse,
			BooleanTrue,
			IntegerLiteral,
			FloatLiteral,
			StringLiteral,
			Identifier,

			// Control
			If,
			While,
			For,
			Yield,
			Break,
			Return,

			// Operators
			Inverse,
			Assign,
			Accessor,

			// ---- Math
			Addition,
			Subtraction,
			Multiplication,
			Division,
			Modulus,
			Increment,
			Decrement,
			Exponent,
			Add,
			Subtract,
			Multiply,
			Divide,
			Modulo,

			// ---- Comparison
			Equal,
			Unequal,
			Lesser,
			Greater,
			LesserOrEqual,
			GreaterOrEqual,
			ValueEqual,
			ValueUnequal,

			// ---- Bitwise
			AND,
			OR,

			// Object
			Class,

			Total
		};

		Type type;

		// ====================================================================================================================================
		// Constructor
		// ====================================================================================================================================

		Token(Type = Type::None);

		// ====================================================================================================================================
		// Category
		// ====================================================================================================================================

		enum class Category
		{
			None,
			DataType,
			Operator,
			Term
		};

		bool isSyntax();
		bool isDataType();
		bool isControl();
		bool isOperator();
		bool isTerm();
		bool is(Category);

		// ====================================================================================================================================
		// Utility
		// ====================================================================================================================================

		std::string toString();
		DataType toType();

		// ====================================================================================================================================
		// Operators
		// ====================================================================================================================================

		bool operator ==(Token);
		bool operator ==(Type);
		bool operator !=(Token);
		bool operator !=(Type);
		Type operator =(Token);
		Type operator =(Type);
	};
}