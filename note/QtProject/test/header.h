#ifndef HEADER_H
#define HEADER_H


#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H


using namespace std;

namespace DLib
{

template <typename T>
class DSharedPointer
{
private:
    T* m_pointer;
    int* m_numsPointTo;

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
                ::delete numsPointTo;
                ::delete toDel;
            }
        }
    }

public:
    DSharedPointer(T* pointer) : m_pointer(NULL), m_numsPointTo(NULL)
    {
        cout << "DSharedPointer(T* pointer)"    << endl;
        if(pointer!=NULL)
        {
            this->m_numsPointTo = ::new int(1);
            if(this->m_numsPointTo!=NULL)
                this->m_pointer = pointer;
            else
                this->m_numsPointTo = NULL;

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


#endif // HEADER_H
