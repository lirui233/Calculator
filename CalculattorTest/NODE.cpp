#include<iostream>
#include "NODE.h"


NODE::NODE()
{
	std::cout <<"NODE::NODE()" << std::endl;
}


NODE::~NODE()
{
	std::cout << "NODE::~NODE()" << std::endl;
}

void NODE::Calc() const
{
	std::cout << "void NODE::Calc() const" << std::endl;
}