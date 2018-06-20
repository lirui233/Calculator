#include<cmath>
#include<cassert>
#include<iostream>
#include "Storage.h"
#include"SymbolTable.h"
Storage::Storage(SymbolTable& tbl)
{
	AddConstants(tbl);
}
void Storage::Serialize(Serializer& out) const
{
	out << cells_.size();
	for (unsigned int i = 0; i < cells_.size();++i)
	{
		out << cells_[i] << inits_[i];
	}
}
void Storage::DeSerialize(DeSerializer& in)
{
	cells_.clear();
	inits_.clear();
	unsigned int size;
	in >> size;
	cells_.resize(size);
	inits_.resize(size);

	for (unsigned int i = 0; i < size; ++i)
	{
		double d;
		bool b;
		in >> d >> b;
		cells_[i]=d;
		inits_[i] = b;
	}
}
void Storage::Clear()
{
	cells_.clear();
	inits_.clear();
}
bool Storage::IsInit(unsigned int id) const
{
	return (id < cells_.size()) && (inits_[id]);
}
void Storage::AddConstants(SymbolTable& tbl)
{
	std::cout << "Variable list:" <<  std::endl;
	unsigned int id = tbl.Add("e");
	AddValue(id, exp(1.0));
	std::cout<<"e=" << exp(1.0) << std::endl;
	id = tbl.Add("PI");
	AddValue(id, 2.0*acos(0.0));
	std::cout << "PI=" << 2.0*acos(0.0) << std::endl;

}
double Storage::GetValue(unsigned int id) const
{
	assert(id <cells_.size());
	return cells_[id];
}
void Storage::SetValue(unsigned int id, double val)
{
	assert(id >=0);   //assert(id <= cells_.size());//д��ط�֮һ���տ�ʼ��ʼ����ʱ��һ���ǵ������С
	if (id < cells_.size())
	{
		cells_[id] = val;
		inits_[id] = true;
	}
	else 
	{
		AddValue(id, val);
	}
}
void Storage::AddValue(unsigned int id, double val)
{
	cells_.resize(id + 1);
	inits_.resize(id + 1);
	cells_[id] = val;
	inits_[id] = true;
}
