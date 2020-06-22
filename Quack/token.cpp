#include "pch.h"
#include "token.h"

qck::Token::Token(Type t) : type(t)
{

}

bool qck::Token::isSyntax()
{
	return type >= Type::ScopeBegin && type <= Type::ScopeEnd;
}

bool qck::Token::isDataType()
{
	return type >= Type::Void && type <= Type::Auto;
}

bool qck::Token::isControl()
{
	return type >= Type::If && type <= Type::Return;
}

bool qck::Token::isOperator()
{
	return type >= Type::Assign && type <= Type::OR;
}

bool qck::Token::isTerm()
{
	return type >= Type::BooleanFalse && type <= Type::Identifier;
}

bool qck::Token::is(Category category)
{
	switch (category)
	{
		case Category::DataType:	return type >= Type::Void && type <= Type::Auto;
		case Category::Operator:	return type >= Type::Assign && type <= Type::OR;
		case Category::Term:		return type >= Type::BooleanFalse && type <= Type::Identifier;
	}

	return false;
}

std::string qck::Token::toString()
{
	switch (type)
	{
		case Token::Type::Invalid:			return "Invalid";
		case Token::Type::ScopeBegin:		return "ScopeBegin";
		case Token::Type::ScopeEnd:			return "ScopeEnd";
		case Token::Type::GroupBegin:		return "GroupBegin";
		case Token::Type::GroupNext:		return "GroupNext";
		case Token::Type::GroupEnd:			return "GroupEnd";
		case Token::Type::LineEnd:			return "LineEnd";
		case Token::Type::Accessor:			return "Accessor";
		case Token::Type::Void:				return "Void";
		case Token::Type::Boolean:			return "Boolean";
		case Token::Type::Integer:			return "Integer";
		case Token::Type::Float:			return "Float";
		case Token::Type::String:			return "String";
		case Token::Type::Auto:				return "Auto";
		case Token::Type::BooleanFalse:		return "BooleanFalse";
		case Token::Type::BooleanTrue:		return "BooleanTrue";
		case Token::Type::IntegerLiteral:	return "IntegerLiteral";
		case Token::Type::FloatLiteral:		return "FloatLiteral";
		case Token::Type::StringLiteral:	return "StringLiteral";
		case Token::Type::If:				return "If";
		case Token::Type::While:			return "While";
		case Token::Type::For:				return "For";
		case Token::Type::Yield:			return "Yield";
		case Token::Type::Break:			return "Break";
		case Token::Type::Return:			return "Return";
		case Token::Type::Inverse:			return "Inverse";
		case Token::Type::Assign:			return "Assign";
		case Token::Type::Addition:			return "Addition";
		case Token::Type::Subtraction:		return "Subtraction";
		case Token::Type::Multiplication:	return "Multiplication";
		case Token::Type::Division:			return "Division";
		case Token::Type::Modulus:			return "Modulus";
		case Token::Type::Increment:		return "Increment";
		case Token::Type::Decrement:		return "Decrement";
		case Token::Type::Exponent:			return "Exponent";
		case Token::Type::Add:				return "Add";
		case Token::Type::Subtract:			return "Subtract";
		case Token::Type::Multiply:			return "Multiply";
		case Token::Type::Divide:			return "Divide";
		case Token::Type::Modulo:			return "Modulo";
		case Token::Type::Equal:			return "Equal";
		case Token::Type::Unequal:			return "Unequal";
		case Token::Type::Lesser:			return "Lesser";
		case Token::Type::Greater:			return "Greater";
		case Token::Type::LesserOrEqual:	return "LesserOrEqual";
		case Token::Type::GreaterOrEqual:	return "GreaterOrEqual";
		case Token::Type::ValueEqual:		return "ValueEqual";
		case Token::Type::ValueUnequal:		return "ValueUnequal";
		case Token::Type::AND:				return "AND";
		case Token::Type::OR:				return "OR";
		case Token::Type::Identifier:		return "Identifier";
		case Token::Type::Class:			return "Class";
	}

	return "";
}

qck::DataType qck::Token::toType()
{
	switch (type)
	{
		case Type::Void:
			return DataType::Void;

		case Type::Boolean:
		case Type::BooleanFalse:
		case Type::BooleanTrue:
			return DataType::Boolean;

		case Type::Integer:
		case Type::IntegerLiteral:
			return DataType::Integer;

		case Type::Float:
		case Type::FloatLiteral:
			return DataType::Float;

		case Type::String:
		case Type::StringLiteral:
			return DataType::String;

		case Type::Auto:
			return DataType::Auto;
	}

	return DataType::None;
}

bool qck::Token::operator ==(Token t)
{
	return type == t.type;
}

bool qck::Token::operator ==(Type t)
{
	return type == t;
}

bool qck::Token::operator !=(Token t)
{
	return type != t.type;
}

bool qck::Token::operator !=(Type t)
{
	return type != t;
}

qck::Token::Type qck::Token::operator =(Token t)
{
	type = t.type;
	return type;
}

qck::Token::Type qck::Token::operator =(Type t)
{
	type = t;
	return type;
}