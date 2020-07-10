#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <cstddef>
namespace DLib{

template<typename T, size_t BlockSize>
class MemoryPool
{
public:
    /*value type define*/
    typedef T        vtype;
    typedef T*       vpointer;
    typedef T&       vreference;
    typedef const T* vconst_pointer;
    typedef const T& vconst_reference;

private:
    union block
    {
        char vdate[1];       //client data
        block* next;         //point to next free block
    };

    block* currentBlock;
    block* currentSlot;
    block* lastSlot;

    void allocateBlock();
};

}/*DLib*/
#endif /*MEMORY_POOL_H*/
