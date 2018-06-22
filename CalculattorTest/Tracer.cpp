#include<iostream>
#include "Tracer.h"
#ifndef NDEBUG
bool Tracer::Ready = false;
Tracer::Tracer() :lockCount_(0)
{
	Ready = true;
}

Tracer::~Tracer()
{
	Ready = false;
	Dump();
}

void Tracer::Add(void *p, const char* file, long line)
{
	if (lockCount_ > 0)
		return;
	Tracer::Lock lock(*this); // 防止调用系统内部的new函数
	//lock();
	mapEntry_[p] = Entry(file, line); // 该位置会再次调用new
	//unlock(); 

}
void Tracer::Remove(void* p)
{
	if (lockCount_ > 0)
		return;

	Tracer::Lock lock(*this);
	//lock();
	std::map<void*, Entry>::iterator it;
	it = mapEntry_.find(p);
	if (it != mapEntry_.end())
	{
		mapEntry_.erase(it);
	}
	//unlock();
}
void Tracer::Dump()
{
	if (mapEntry_.size() > 0)
	{
		std::cout << "*** Memory leak(s):" << std::endl;
		std::map<void*, Entry>::iterator it;
		for (it = mapEntry_.begin(); it != mapEntry_.end(); ++it)
		{
			const char* file = it->second.File();
			long line = it->second.Line();
			int addr = reinterpret_cast<int>(it->first);
			std::cout << "0x" << std::hex << addr << ":"
				<< file << ",line" << std::dec << line << std::endl;
		}
		std::cout << std::endl;
	}
}

Tracer NewTrace;

void* operator new(size_t size, const char* file, long line)
{
	void* p = malloc(size);
	if (Tracer::Ready)
	{
		NewTrace.Add(p, file, line);
	}
	return p;

}
void  operator delete(void*p, const char*, long)
{
	if (Tracer::Ready)
	{
		NewTrace.Remove(p);
	}
	free(p);
}
//void* operator new(size_t size)
//{
//	void* p = malloc(size);
//	if (Tracer::Ready)
//	{
//		NewTrace.Add(p, "?", 0);
//	}
//	return p;
//}
void  operator delete(void*p)
{
	if (Tracer::Ready)
	{
		NewTrace.Remove(p);
	}
	free(p);
}
void* operator new[](size_t size, const char* file, long line)
{
	void* p = malloc(size);
	if (Tracer::Ready)
	{
		NewTrace.Add(p, file, line);
	}
	return p;
}
void  operator delete[](void*p, const char*, long)
{
	if (Tracer::Ready)
	{
		NewTrace.Remove(p);
	}
	free(p);
}
void* operator new[](size_t size)
{
	void* p = malloc(size);
	if (Tracer::Ready)
	{
		NewTrace.Add(p, "?", 0);
	}
	return p;

}
void operator delete[](void*p)
{
	if (Tracer::Ready)
	{
		NewTrace.Remove(p);
	}
	free(p);
}

#endif  // NDEBUG