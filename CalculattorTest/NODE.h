#ifndef _NODE_H_
#define _NODE_H_
class NODE
{
public:
	NODE();
	~NODE();
	void Calc() const;
};

class NodePtr
{
public:
	explicit NodePtr(NODE* ptr=0)
		:ptr_(ptr) {}

	NodePtr( NodePtr& other)
		:ptr_(other.Release()) {}	

	~NodePtr() { delete ptr_; }
	
	NodePtr& operator=(NodePtr& other)
	{
		Reset(other.Release());
		return *this;
	}

	NODE& operator*()  const { return *Get(); }

	NODE* operator->() const { return Get(); }

	NODE* Get()  const { return ptr_; }

	NODE* Release() // ´«µÝÖ¸Õë
	{
		NODE* tmp = ptr_;
		ptr_ = 0;
		return tmp;
	}	 
	void Reset(NODE* ptr = 0)
	{
		if (ptr_ != ptr)
		{
			delete ptr_;
		}
		ptr_ = ptr;
	}
		
private:
	NODE* ptr_;
};
#endif   //_NODE_H_

