#include<iostream>
#include "Calc.h"

void Calc::Serialize(Serializer& out) const
{
	symtbl_.Serialize(out);
	storage_.Serialize(out);
}
void Calc::DeSerialize(DeSerializer& in)
{
	symtbl_.DeSerialize(in);
	storage_.DeSerialize(in);
}
unsigned int Calc::FindSymbol(const std::string& str) const
{
	return symtbl_.Find(str);
}
unsigned int Calc::AddSymbol(const std::string& str)
{
	return symtbl_.Add(str);
}

void Calc::ListFun() const
{
	for (unsigned int i = 0; i < funTbl_.GetSize(); ++i)
	{
		std::cout << symtbl_.GetSymbolName(i) << std::endl;
	}
}
void Calc::ListVar() const
{
	for (unsigned int i = funTbl_.GetSize(); i < symtbl_.GetCurId(); ++i)
	{
		std::string name=symtbl_.GetSymbolName(i);
		double val;
		if (GetVariableValue(i, val))

			std::cout << name << "=" << val << std::endl;
		else
			std::cout << name << "=?"<< std::endl;
	}
}

bool Calc::GetVariableValue(unsigned int id, double& val) const
{
	if (storage_.IsInit(id))
	{
		val = storage_.GetValue(id);
		return true;
	}
	return false;
}
