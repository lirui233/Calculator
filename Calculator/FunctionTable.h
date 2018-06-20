#ifndef _FUNCTIONTABLE_H_
#define _FUNCTIONTABLE_H_
class SymbolTable;

typedef double (*PtrFun)(double);

class FunctionTable
{
public:
	FunctionTable(SymbolTable& tbl);
	~FunctionTable();
	void Init(SymbolTable& tbl);
	unsigned int size() const
	{
		return size_;
	}
	PtrFun GetFunction(unsigned int id) const
	{
		return pFuns_[id];
	}
	unsigned int GetSize() const  { return size_; }
private:
	PtrFun* pFuns_;
    unsigned int size_;
};
#endif //_FUNCTIONTABLE_H_
