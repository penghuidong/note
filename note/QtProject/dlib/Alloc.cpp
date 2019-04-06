
#ifndef ALLOC_H_
#define ALLOC_H_
#include "Alloc.h"

namespace DLib {

mallocAlloc::mallocErrHandler mallocAlloc::handler = NULL;

size_t MemoryPoolAlloc::poolSize   = 0;

char*  MemoryPoolAlloc::startPool = NULL;

char*  MemoryPoolAlloc::endPool   = NULL;


typename MemoryPoolAlloc::Block*
MemoryPoolAlloc::freeBlockList[MemoryPoolAlloc::FREELISTNUM] =
{
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL
};


}


#endif
