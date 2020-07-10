#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "DObject.h"
#include "DException.h"

using namespace std;

namespace DLib
{

template <typename T>
class DSharedPointer : public DObject<>
{
private:
    T* m_pointer;
    int* m_numsPointTo;

public:
    void clear()
    {
        T* toDel = this->m_pointer;
        int* numsPointTo = this->m_numsPointTo;
        this->m_pointer = NULL;
        this->m_numsPointTo = NULL;
        if(numsPointTo)
        {
            (*numsPointTo)--;
            if(*numsPointTo==0)
            {
                delete numsPointTo;
                delete toDel;
            }
        }
    }

public:
    DSharedPointer(T* pointer) : m_pointer(NULL), m_numsPointTo(NULL)
    {
        if(pointer!=NULL)
        {
            cout << "pointer:" << pointer << endl;
            this->m_numsPointTo = static_cast<int*>(DObject<>::operator new(sizeof(int)));
            if(this->m_numsPointTo!=NULL)
                this->m_pointer = pointer;
            else
                throw_exception(outOfMemory, "no memory to create DSharedPointer");
        }
    }

    DSharedPointer(const DSharedPointer<T>& rval) : m_pointer(NULL), m_numsPointTo(NULL)
    {
        this->m_numsPointTo = rval.m_numsPointTo;
        this->m_pointer = rval.m_pointer;
        if(this!=&rval)
            (*this->m_numsPointTo)++;
    }

    DSharedPointer& operator =(const DSharedPointer<T>& rval)
    {
        cout << "DSharedPointer& operator =" << endl;
        if(this!=&rval)
        {
            clear();
            this->m_numsPointTo = rval.m_numsPointTo;
            this->m_pointer = rval.m_pointer;
            if(m_numsPointTo!=NULL)
                *m_numsPointTo--;
        }
        return *this;
    }

    ~DSharedPointer()
    {
        clear();
    }



};

}

#endif // SHAREDPOINTER_H
