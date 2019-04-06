#ifndef DSTACK_H
#define DSTACK_H


#include "DVector.h"
#include "DException.h"

namespace DLib {

template<typename T>
class DStack
{
private:
    DVector<T> mstack;
public:
    void push(const T& val){mstack.pushBack(val);}

    T pop() {return mstack.popFront();}

    size_t size() const{return mstack.length();}

    T& top(){return mstack.operator [](mstack.length()-1);}

    bool empty() const{return !mstack.length();}
};


}




#endif // DSTACK_H
