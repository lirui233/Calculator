#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_
#include<exception>
#include<string>

class Exception: public std::exception
{
public:
	explicit Exception(const char* message):
		message_(message)
	{
		FillStackTrace();
	}
	explicit Exception(const std::string& message) :
		message_(message)
	{
		FillStackTrace();
	}
	virtual ~Exception() throw()
	{

	}
	virtual const char* what() const throw(); //不进行抛出异常
    const char* StackTrace() const throw();
	
private:
	void FillStackTrace();
	std::string message_;
	std::string stackTrace_;

};

class SyntaxError :public Exception // 语法错误
{
public:
	explicit SyntaxError(const char* message) :
		Exception(message)
	{

	}
	explicit SyntaxError(const std::string& message) :
		Exception(message)
	{

	}
	virtual ~SyntaxError() throw()
	{

	}
};

class FileStreamError :public Exception
{
public:
	explicit FileStreamError(const char* message) :
		Exception(message)
	{

	}
	explicit FileStreamError(const std::string& message) :
		Exception(message)
	{

	}
	virtual ~FileStreamError() throw()
	{

	}
};
#endif //_EXCEPTION_H_

