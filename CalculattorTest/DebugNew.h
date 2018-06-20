#ifndef DEBUGNEW_H_
#define DEBUGNEW_H_

#ifndef NDEBUG
#include"Tracer.h"
#define new  new(__FILE__,__LINE__)

#endif  //NDEBUG
#endif  //DEBUGNEW_H_