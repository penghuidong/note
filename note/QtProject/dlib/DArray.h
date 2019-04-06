#ifndef DARRAY_H
#define DARRAY_H

#include "DObject.h"
#include "DException.h"

namespace DLib
{

template<typename T>
class DArray : public DObject<>
{
private:
    T* mstart;
    size_t mnumber;
private:
    void fill(size_t num, const T& val);

    void clear();

public:
    DArray(size_t num);

    bool set(size_t index, const T& val);

    bool get(size_t index, T& val);

    T* resize(size_t newsize);

    size_t length() const {return mnumber;}

    size_t remove_if(const T& val);

    T& operator[](size_t index);

    ~DArray();

};

template<typename T>
void DArray<T>::fill(size_t num, const T& val)
{
    for(size_t i=0; i<num; i++)
        ::new (mstart+i) T(val);
}

template<typename T>
void DArray<T>::clear()
{
    for(size_t i=0; i<mnumber; i++)
        (mstart+i)->~T();
    DObject<>::operator delete[](mstart);
    mnumber = 0;
}

template<typename T>
DArray<T>::DArray(size_t num) : mnumber(num)
{
    if(num>0){
        mstart = static_cast<T*>(DObject<>::operator new[](sizeof(T)*num));
        fill(num, T());
    }else
        throw_exception(invalidParameter,"DArray's length must biger than 0");
}

template<typename T>
bool DArray<T>::set(size_t index, const T& val)
{
     bool checkindex = 0<=index && index<mnumber;
     if(checkindex)
         mstart[index] = val;
     return checkindex;
}

template<typename T>
bool DArray<T>::get(size_t index, T& val)
{
    bool checkindex = 0<=index && index<mnumber;
    if(checkindex)
        val = mstart[index];
    return checkindex;
}

template<typename T>
T* DArray<T>::resize(size_t newsize)
{
    if(newsize<=mnumber)
    {
        for(size_t i=newsize; i<mnumber; i++)
            (mstart+i)->~T();
        mnumber = newsize;
    }
    else if(newsize>mnumber)
    {
        T* newstart = static_cast<T*>(DObject<>::operator new[](sizeof(T)*newsize));
        for(size_t i=0; i<mnumber; i++)
            newstart[i] = mstart[i];
        for(size_t i=mnumber; i<newsize; i++)
            ::new (newstart+i) T();
        mnumber = newsize;
        mstart = newstart;
    }
    return mstart;
}


template<typename T>
size_t DArray<T>::remove_if(const T& val)
{
    size_t count = 0;
    for(size_t i=0; i<mnumber; i++)
        if(mstart[i]==val){
            (mstart+i)->~T();
            count++;
        }
    return count;
}

template<typename T>
T& DArray<T>::operator[](size_t index)
{
    if(0<=index && index<mnumber)
       return  mstart[index];
    else
        throw_exception(indexOutOfRange, "index out of range in DArray operator [] operation");
}

template<typename T>
DArray<T>::~DArray()
{
    clear();
}



}



#endif // DARRAY_H
