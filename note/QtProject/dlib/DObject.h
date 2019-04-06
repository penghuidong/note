#ifndef DOBJECT_H
#define DOBJECT_H

#include "Alloc.h"
#include "Config.h"

namespace DLib
{
template<class Alloc = poolAlloc>
class DObject
{
private:
    enum {MaxBytesPerObj=128};

    size_t each_size;

    void get(){each_size = newsize;}
    void set(){newsize = each_size;}

    static size_t newsize;

public:
    DObject() : each_size(0) {
#ifdef USE_DDEBUG
        cout << "DObject::DObject()" << endl;
#endif
        get();
    }

    static void* operator new (size_t size) throw();

    static void  operator delete(void* addr);

    static void* operator new[](size_t size) throw();

    static void  operator delete[](void* addr);

    bool  operator==(const DObject& obj);

    bool  operator!=(const DObject& obj);

    virtual ~DObject()=0;
};


template<class Alloc>
size_t DObject<Alloc>::newsize = 0;


template<class Alloc>
void* DObject<Alloc>::operator new(size_t size) throw()
{
    newsize = size;
#ifdef USE_DDEBUG
    cout << "DObject::operator new " << size  << " bytes"<<  endl;
#endif
    return Alloc::allocate(size);
}


template<class Alloc>
void  DObject<Alloc>::operator delete(void* addr)
{
    if(newsize>MaxBytesPerObj)
    {
#ifdef USE_DDEBUG
        cout << "DObject::operator delete: use c deallocate " << newsize
              << " bytes "<< endl;
#endif
        mallocAlloc::deallocate(addr);
    }
    else if(newsize<=MaxBytesPerObj)
    {
#ifdef USE_DDEBUG
        cout << "DObject::operator delete: use pool deallocate " << newsize
             <<" bytes" << endl;
#endif
        poolAlloc::deallocate(addr, newsize);
    }
}

template<class Alloc>
void* DObject<Alloc>::operator new[](size_t size) throw()
{
    newsize = size;
#ifdef USE_DDEBUG
    cout << "DObject::operator new[] "<< size << " bytes" << endl;
#endif
    return Alloc::allocate(size);
}

template<class Alloc>
void  DObject<Alloc>::operator delete[](void* addr)
{
    if(newsize>MaxBytesPerObj)
    {
#ifdef USE_DDEBUG
        cout << "DObject::operator delete[]: use c deallocate " << newsize
              << " bytes " << endl;
#endif
        MemoryPoolAlloc::deallocate(addr, newsize);
    }
    else if(newsize<=MaxBytesPerObj)
    {
#ifdef USE_DDEBUG
        cout << "DObject::operator delete[]: use pool deallocate " << newsize
             << " bytes"<< endl;
#endif
        mallocAlloc::deallocate(addr);
    }
}

template<class Alloc>
bool  DObject<Alloc>::operator==(const DObject& obj)
{
#ifdef USE_DDEBUG
    cout << "DObject::operator==" << endl;
#endif
    return this==&obj;
}

template<class Alloc>
bool  DObject<Alloc>::operator!=(const DObject& obj)
{
#ifdef USE_DDEBUG
    cout << "DObject::operator!=" << endl;
#endif
    return this!=&obj;
}

template<class Alloc>
DObject<Alloc>::~DObject()
{
#ifdef USE_DDEBUG
    cout << "DObject::~DObject()" << endl;
#endif
    set();
}

} /*DLib*/
#endif // DOBJECT_H
