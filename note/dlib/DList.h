#ifndef DLIST_H
#define DLIST_H

#include "DObject.h"

namespace  DLib {

template<typename T>
class DList
{
public:
    virtual bool insert(size_t index, const T& elem) =0;
    virtual T remove(size_t index) = 0;
    virtual bool set(size_t index, const T& elem) = 0;
    virtual size_t  find(const T& elem) const  = 0;
    virtual bool get(size_t index, T& elem) const = 0;
    virtual size_t length() const = 0;
    virtual void clear() = 0;
};

}

#endif // DLIST_H
