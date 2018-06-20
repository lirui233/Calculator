#include<cctype>
#include<iostream>
#include "Scanner.h"
Scanner::Scanner(std::istream& in) :in_(in)   /*curPos_(0)*/  //��ֵδ��ʼ�������ˣ�0��
{
	Accept();         //��ѧ������ʱ������������������ˣ����������ĳ���д��һ�߳���һ��ѧ��һ����⣬
	isEmpty_ = (token_==TOKEN_END);  //������������ⲻ�˵ģ������ܲ��ԣ���ͷ���Ҳ������������֪���¡�
}
bool Scanner::IsEmpty() const
{
	return isEmpty_;
}
bool Scanner::IsDone() const
{
	return token_==TOKEN_END;
}
bool Scanner::IsCommand() const
{
	return token_ == TOKEN_COMMAND;
}
double Scanner::Number() const
{
	return number_;	
}
std::string Scanner::GetSymbol() const
{
	return symbol_;
}
EToken Scanner::Token() const
{
	return token_;
}

//void Scanner::SkipWhite()
//{
//	while (isspace(buf_[curPos_]))
//		++curPos_;
//}
void Scanner::Readchar()
{
	look_ = in_.get();
	while (look_ == ' ' || look_ == '\t')
		look_ = in_.get();
}
void Scanner::Accept()
{
	Readchar();
	switch (look_)
	{ 
	case'!':
		token_ = TOKEN_COMMAND;
		//++curPos_;
		break;
	case'+':
		token_ = TOKEN_PLUS;
		//++curPos_;
		break;
	case'-':
		token_ = TOKEN_MINUS;
		//++curPos_;
		break;
	case'*':
		token_ = TOKEN_MULTIPLY;
		//++curPos_;
		break;
	case'/':
		token_ = TOKEN_DIVIDE;
		//++curPos_;
		break;
	case'=':
		token_ = TOKEN_ASSIGN;
		//++curPos_;
		break;
	case'(':
		token_ = TOKEN_LPARENTHESIS;
		//++curPos_;
		break;
	case')':
		token_ = TOKEN_RPARENTHESIS;
		//++curPos_;
		break;
	case'0':case'1':case'2':case'3':case'4':
	case'5':case'6':case'7':case'8':case'9':
	case'.':
		token_ = TOKEN_NUMBER;
		in_.putback(look_);
		in_ >> number_;
		//char *p;
		//number_=strtod(&buf_[curPos_], &p);
		//curPos_ = p - &buf_[0];
		break;
	case'\0':case'\n':case'\r':case EOF:
		token_ = TOKEN_END;         //�ⶼ��д�ˣ�Ҫ���Ǽ��bug�������ֲ��ˡ�
		break;
	default:
		if ((isalpha(look_))|| (look_ == '_'))
		{
			token_ = TOKEN_IDENTIFIER;
			symbol_.erase();
			//char ch = buf_[curPos_];
			do
			{
				symbol_ += look_;
				look_ = in_.get();

				//ch = buf_[++curPos_];
			} while (isalnum(look_)||look_=='_');
			in_.putback(look_);
		}
		else
		{
            token_ = TOKEN_ERROR;
		}		
		break;
	}
}

void Scanner::AcceptCommand()
{
	Readchar();
	symbol_.erase();
	while (!isspace(look_))
	{
		symbol_ += look_;
		look_ = in_.get();
	}
}