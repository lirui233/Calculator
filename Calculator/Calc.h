#ifndef _CALC_H_
#define _CALC_H_
#include<string>
#include"SymbolTable.h"
#include"Storage.h"
#include"FunctionTable.h"
#include"Serial.h"

class Parser;//此处总是会把Parser写成Paser，单词拼不对害死人
class Calc : public Serializable
{
	friend  class Parser;
public:
	Calc():storage_(symtbl_),funTbl_(symtbl_) {}
	void Serialize(Serializer& out) const;
	void DeSerialize(DeSerializer& in);
	void ListFun() const;
	void ListVar() const;
private:

	bool GetVariableValue(unsigned int id, double& val) const;
	Storage& GetStorage() 
	{
		return storage_;
	}
	PtrFun GetFunction(unsigned int id) const
	{
		return funTbl_.GetFunction(id);
	}
	bool IsFunction(unsigned int id) const
	{
		return id < funTbl_.size();
	}
	unsigned int AddSymbol(const std::string& str);
	unsigned int FindSymbol(const std::string& str) const;
	SymbolTable symtbl_;	
	FunctionTable funTbl_;//固定的
    Storage storage_;//非固定的
};
#endif //_CALC_H_

