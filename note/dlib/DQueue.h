#ifndef DQUEUE_H
#define DQUEUE_H

#include "DSingleLinkList.h"

namespace DLib {

template <typename T>
class DQueue
{
private:
    DSingleLinkList<T> mqueue;
public:
    DQueue() {}

    void push(const T& val){mqueue.insert(0, val); }

    T pop(){return mqueue.remove(mqueue.length()-1);}

    T front()const{return mqueue[mqueue.length()-1];}

    size_t length() const{return mqueue.length();}

    bool empty() const{return !mqueue.length();}
};


}


#endif // DQUEUE_H
