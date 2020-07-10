#ifndef DVECTOR_H
#define DVECTOR_H

#include "DObject.h"
#include "DException.h"

namespace DLib {

template<typename T>
class DVector : public DObject<>
{
private:
    typedef T* tpointer;
    tpointer mstart;
    size_t mlength;
    size_t mcapacity;

private:
    size_t raiseUpCapacity(size_t length);

    void fill(T* startadd,size_t num, const T& val);

public:
    void clear();

public:
    DVector();

    DVector(size_t num);

    DVector(size_t num, const T& val);

    size_t capacity() const {return mcapacity;}

    size_t length() const {return mlength;}

    bool insert(size_t index, const T& val);

    bool insert(size_t index, size_t num, const T& val);

    T remove(size_t index);

    T remove(size_t index, size_t num);

    T popBack();

    T popFront();

    bool pushBack(const T &val);

    bool pushFront(const T& val);

    ~DVector();
public:
    T& operator[](size_t index);
};

template<typename T>
size_t DVector<T>::raiseUpCapacity(size_t length)
{
    return length<=8 ? ( length==0 ? 8: length*2 ): length+8;
}

template<typename T>
void DVector<T>::fill(T* startadd,size_t num, const T& val)
{
    if(startadd!=NULL)
    {
        for(size_t i=0; i<num; i++)
            ::new (startadd+i) T(val);
    }
}

template<typename T>
void DVector<T>::clear()
{
    if(mstart!=NULL)
    {
        for(size_t i=0; i<mlength; i++)
            (mstart+i)->~T();
        mlength = 0;
    }
}

template<typename T>
DVector<T>::DVector() : mlength(0)
{
    mcapacity = raiseUpCapacity(0);
    mstart = static_cast<tpointer>(DObject<>::operator new[](sizeof(T)*mcapacity));
}


template<typename T>
DVector<T>::DVector(size_t num)
{
    mcapacity = raiseUpCapacity(num);
    mstart = static_cast<tpointer>(DObject<>::operator new[](sizeof(T)*mcapacity));
    mlength = num;
    fill(mstart, num, T());
}

template<typename T>
DVector<T>::DVector(size_t num, const T& val)
{
    mcapacity = raiseUpCapacity(num);
    mstart = static_cast<tpointer>(DObject<>::operator new[](sizeof(T)* mcapacity));
    mlength = num;
    fill(mstart, num, T(val));
}

template<typename T>
bool DVector<T>::insert(size_t index, const T& val)
{
    return insert(index, 1, val);
}


template<typename T>
bool DVector<T>::insert(size_t index, size_t num, const T& val)
{
    bool checkIndex = (0<=index);
    if(checkIndex)
    {
        if(mcapacity-mlength>=num)
        {
            if(index<mlength)
            {
                for(size_t i=mlength-1; i>=index && i!=0; i--)
                    mstart[i+num] = mstart[i];
                for(size_t i=0; i<num; i++)
                    ::new (mstart+index+i) T(val);
                mlength += num;
            }
            else if(index>=mlength)
            {
                for(size_t i=0; i<num; i++)
                    ::new (mstart+mlength+i) T(val);
                mlength+=num;
            }
        }
        else
        {
            T* newStart = static_cast<T*>(DObject<>::operator new[](sizeof(T)*2*mcapacity));
            if(newStart) {
                for(size_t i=0; i<index; i++)
                    newStart[i] = mstart[i];
                for(size_t i=0; i<num; i++)
                    ::new (newStart+index+i) T(val);
                if(index<mlength-1)
                    for(size_t i=0; i<mlength-index; i++)
                        newStart[index+num+i] = mstart[index+i];
            }
            mstart = newStart;
            mcapacity = 2*mcapacity;
            mlength += num;
        }
    }
    return checkIndex;
}


template<typename T>
T DVector<T>::remove(size_t index)
{
    return remove(index,1);
}

template<typename T>
T DVector<T>::remove(size_t index, size_t num)
{
    if(0<=index && index<mlength)
    {
        T ret = mstart[index];
        for(size_t i=index; i<mlength; i++)
            mstart[i] = mstart[i+num];
        mlength-=num;
        return ret;
    }else {
        throw_exception(indexOutOfRange, "index out of range in DVector::remove");
    }
}

template<typename T>
T DVector<T>::popBack()
{
    return remove(mlength-1, 1);
}

template<typename T>
T DVector<T>::popFront()
{
    return remove(0,1);
}

template<typename T>
bool DVector<T>::pushBack(const T& val)
{
    return insert(mlength, val);
}

template<typename T>
bool DVector<T>::pushFront(const T& val)
{
    return insert(0, val);
}

template<typename T>
DVector<T>::~DVector()
{
    clear();
   // DObject<>::operator delete[](mstart);
}

template<typename T>
T& DVector<T>::operator[](size_t index)
{
    if(0<=index && index<mlength)
        return *(mstart+index);
    else
        throw_exception(indexOutOfRange, "index out of range");
}

}  // namespact DLib



#endif // DVECTOR_H
