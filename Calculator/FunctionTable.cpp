#include<cmath>
#include<cassert>
#include<iostream>
#include"SymbolTable.h"
#include"FunctionTable.h"
#include"DebugNew.h"
struct FunctionEntry
{
	PtrFun pFun_;
	char* funName_;
};
FunctionEntry Entrys[] =
{ 
	log,     "log",
	log10,   "log10",
	exp,     "exp",
	sqrt,    "sqrt",
	sin,     "sin",
	cos,     "cos",
	tan,     "tan",
	sinh,    "sinh",
	cosh,    "cosh",
	tanh,    "tanh",
	asin,    "asin",
	acos,    "acos",
	atan,    "atan"

};
FunctionTable::FunctionTable(SymbolTable& tbl)
	:size_(sizeof(Entrys)/sizeof(Entrys[0]))
{
	Init(tbl);
}

void FunctionTable::Init(SymbolTable& tbl)
{
    std::cout << "Function list" << std::endl;
    pFuns_ = new PtrFun[size_];
for (unsigned int i = 0; i < size_; ++i)
	{
		pFuns_[i] = Entrys[i].pFun_;
		unsigned int j = tbl.Add(Entrys[i].funName_);
		assert(i == j);
		std::cout << Entrys[i].funName_ << std::endl;
	}
}

FunctionTable::~FunctionTable()
{
	delete[] pFuns_;
	
}
