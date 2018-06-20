#include<cassert>
#include<cstring>
#include<iostream>
#include<sstream>
#include "Parser.h"
#include"Scanner.h"
#include"Node.h"
#include"Calc.h"
#include"Exception.h"
#include"DebugNew.h"

Parser::Parser(Scanner& scanner, Calc& calc) 
	:scanner_(scanner), calc_(calc), tree_(0), status_(STATUS_OK)
{
}
Parser::~Parser()
{
	// delete tree_; 
}
STATUS Parser::Parse()
{
	tree_=Expr();
	if (!scanner_.IsDone())
	{
		status_ = STATUS_ERROR;
	}
	return status_;
}
std::auto_ptr<Node> Parser::Expr()
{
	std::auto_ptr<Node> node = Term();
	EToken token = scanner_.Token();
	/*if (token == TOKEN_PLUS)
	{
		scanner_.Accept();
		Node* nodeRight = Expr();
		node = new AddNode(node, nodeRight);
	}
	else if (token == TOKEN_MINUS)
	{
		scanner_.Accept();
		Node* nodeRight = Expr();
		node = new SubNode(node, nodeRight);
	}*/
	if (token == TOKEN_PLUS || token == TOKEN_MINUS)
	{
		//Expr:=Term+/-Term
		//MultipleNode* multipleNode = new SumNode(node);
		std::auto_ptr<MultipleNode> multipleNode(new SumNode(node));
		do
		{
			scanner_.Accept();
			std::auto_ptr<Node> nextNode = Term();
			multipleNode->AppendChild(nextNode, (token == TOKEN_PLUS));
			token = scanner_.Token();
		} while (token == TOKEN_PLUS || token == TOKEN_MINUS);
		node = multipleNode;
	}
	else if (token == TOKEN_ASSIGN)
	{
		scanner_.Accept();
		std::auto_ptr<Node> nodeRight = Expr();
		if (node->IsLvalue())
		{
			node = std::auto_ptr<Node> (new AssignNode(node, nodeRight));
		}
		else
		{
			status_ = STATUS_ERROR;
			// to do try
			//std::cout << "the left hand side of an  assignement must be a variable" << std::endl;
			throw SyntaxError("the left-hand side of an  assignement must be a variable");
		}
	}
	return node;
}
std::auto_ptr<Node> Parser::Term()
{
	std::auto_ptr<Node> node = Factor();
	EToken token = scanner_.Token();
	/*if (token == TOKEN_MULTIPLY)
	{
		scanner_.Accept();
		Node* nodeRight = Term();
		node = new MultiplyNode(node, nodeRight);
	}
	else if (token == TOKEN_DIVIDE)
	{
		scanner_.Accept();
		Node* nodeRight = Term();
		node = new DivideNode(node, nodeRight);
	}*/
	if (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE)
	{//Expr:=Factor*(or)/Factor
		//MultipleNode* multipleNode = new ProductNode(node);
		std::auto_ptr<MultipleNode> multipleNode(new ProductNode(node));
		do
		{
			scanner_.Accept();
			std::auto_ptr<Node> nextNode = Factor();
			multipleNode->AppendChild(nextNode, (token == TOKEN_MULTIPLY));
			token = scanner_.Token();
		} while (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE);
		node = multipleNode;
	}
	return node;  
}
std::auto_ptr<Node> Parser::Factor()
{
	std::auto_ptr<Node> node; // Node* node=0;
	EToken token = scanner_.Token();
	if (token == TOKEN_LPARENTHESIS)
	{
		scanner_.Accept();
		node = Expr();
		if (scanner_.Token() == TOKEN_RPARENTHESIS)
		{
			scanner_.Accept();
		} 
		else
		{
			status_ = STATUS_ERROR;
			//to do try 
			//std::cout << "" << std::endl;
			throw SyntaxError("缺少右括号");
			//node = 0;
		}
	}
	else if (token==TOKEN_NUMBER)
	{
		node = std::auto_ptr<Node>( new NumberNode(scanner_.Number()));
		scanner_.Accept();
	}
	else if (token == TOKEN_IDENTIFIER)
	{
		std::string symbol = scanner_.GetSymbol();
		unsigned int id = calc_.FindSymbol(symbol);
		scanner_.Accept();

		if (scanner_.Token() == TOKEN_LPARENTHESIS)
		{
			scanner_.Accept();
			node = Expr();
			if (scanner_.Token() == TOKEN_RPARENTHESIS)
			{
				scanner_.Accept();
				if (id != SymbolTable::IDNOTFOUND&&calc_.IsFunction(id))
				{
					node = std::auto_ptr<Node>(new FunctionNode(node, calc_.GetFunction(id)));
				}
				else
				{
					status_ = STATUS_ERROR;
					//std::cout << "Unkown function" <<"\""<< symbol <<"\""<< std::endl;
					char buf[256] = { 0 };
					//sprintf_s(buf, "Unkown function \"%s\" .", symbol.c_str());  //(也可以的)
					std::ostringstream oss;
					oss << "Unkown function \" " << symbol << " \".";

					throw SyntaxError(oss.str());
				}
			}
			else
			{
				//std::cout << "Missing RPARENTHESIS function" << std::endl;
				throw SyntaxError("Missing RPARENTHESIS function");
			}
		}
		else
		{
            if (id == SymbolTable::IDNOTFOUND)
		  {
			id=calc_.AddSymbol(symbol);
		  }
			node = std::auto_ptr<Node>(new VariableNode(id, calc_.GetStorage()));
		}				
	}
	else if (token==TOKEN_MINUS)
	{
		scanner_.Accept();
		node = std::auto_ptr<Node>( new UMinusNode(Factor()));
	}
	else 
	{
		status_ = STATUS_ERROR;
		//to do try
		//std::cout << "不是一个有效表达式" << std::endl;
		throw SyntaxError("不是一个有效表达式");
		//node = 0;
	}
    return node;
}
double Parser::Calculate() const
{
	assert(tree_.get()!= 0);
	return  tree_->Calc();
}



