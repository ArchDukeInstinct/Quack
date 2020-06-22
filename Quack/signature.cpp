#include "pch.h"
#include "signature.h"
#include "instruction.h"

qck::Compilation::Signature::Signature() :
	dataType(DataType::None)
{

}

qck::Compilation::Signature::Signature(const std::string& name) :
	dataType(DataType::None),
	identifier(name)
{

}

qck::Compilation::Signature::Signature(const std::string& name, const std::vector<DataType>& params) :
	dataType(DataType::None),
	identifier(name),
	parameters(params)
{

}
qck::Compilation::Signature::Signature(DataType type, const std::string& name, const std::vector<DataType>& params) :
	dataType(type),
	identifier(name),
	parameters(params)
{

}

qck::Compilation::Signature::Signature(const Signature& signature) :
	dataType(signature.dataType),
	identifier(signature.identifier),
	parameters(signature.parameters)
{

}

qck::Compilation::Signature::~Signature()
{

}

bool qck::Compilation::Signature::compareParameters(const Signature& a, const Signature& b)
{
	if (a.parameters.size() != b.parameters.size())
		return false;

	for (int i = 0, s = a.parameters.size(); i < s; ++i)
		if (a.parameters[i] != b.parameters[i])
			return false;

	return true;
}

qck::Compilation::SignatureObject::SignatureObject(const Signature& s, Signature::Type t, int i) :
	signature(s),
	type(t),
	id(i)
{

}

qck::Compilation::SignatureMap::SignatureMap()
{
	insert({DataType::Void, "write", {DataType::String, DataType::None}}, Signature::Type::Builtin, (int) Runtime::Instruction::FnWrite);
}

qck::Compilation::SignatureMap::~SignatureMap()
{

}

qck::Compilation::SignatureList* qck::Compilation::SignatureMap::getList(const Signature& signature)
{
	SignatureList* list;

	auto it = signatures.find(signature.identifier);
	if (it == signatures.end())
	{
		list = new SignatureList();
		signatures.insert({signature.identifier, list});
	}
	else
		list = it->second;

	return list;
}

qck::Compilation::SignatureList* qck::Compilation::SignatureMap::getList(const Signature& signature) const
{
	auto it = signatures.find(signature.identifier);
	return it != signatures.end() ? it->second : nullptr;
}

qck::Compilation::SignatureObject* qck::Compilation::SignatureMap::match(SignatureList* list, const Signature& signature) const
{
	for (auto it = list->begin(), end = list->end(); it != end; ++it)
		if (Signature::compareParameters(signature, it->getSignature()))
			return &*it;

	return nullptr;
}

void qck::Compilation::SignatureMap::insert(const Signature& signature, Signature::Type t, int i)
{
	SignatureList* list = getList(signature);
	if (match(list, signature) != nullptr)
		throw "Signature already exists";

	list->push_front({signature, t, i});
}

const qck::Compilation::SignatureObject* qck::Compilation::SignatureMap::search(const std::string& name) const
{
	Signature signature(name);
	SignatureList* list		= getList(signature);
	SignatureObject* item	= match(list, signature);

	return item;
}

const qck::Compilation::SignatureObject* qck::Compilation::SignatureMap::search(const std::string& name, const std::vector<DataType>& params) const
{
	Signature signature(name, params);
	SignatureList* list		= getList(signature);
	SignatureObject* item	= match(list, signature);

	return item;
}