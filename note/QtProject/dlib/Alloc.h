#ifndef ALLOC_H
#define ALLOC_H

#include <cstddef>
#include <cstdlib>
#include <cstring>   //memcpy
#include <iostream>
#include "Config.h"

namespace DLib
{

using std::cerr;
using std::endl;
using std::cout;

class mallocAlloc
{
private:
    static void* malloc_doerr(size_t num)
    {
#ifdef USE_DEBUG
        cout << "mallocAlloc::  malloc_doerr" << endl;
#endif
        void (*MyMallocErrHandler)();
        void* ret;
        for(;;)
        {
            MyMallocErrHandler = handler;
            if(MyMallocErrHandler==NULL)
            {
                cerr << "out of memory" << endl;
                exit(1);
            }
            MyMallocErrHandler();
            ret = malloc(num);
            if(ret)
                return ret;
        }
    }

    static void* realloc_doerr(void* addr, size_t newsz)
    {
#ifdef USE_DEBUG
        cout << "mallocAlloc::  realloc_doerr" << endl;
#endif
        void(*MyReallocErrHandler)();
        void* ret;

        for(;;)
        {
            MyReallocErrHandler = handler;
            if(MyReallocErrHandler==NULL)
            {
                cerr << "out of memory" << endl;
                exit(1);
            }
            MyReallocErrHandler();
            ret = realloc(addr, newsz);
            if(ret)
                return ret;
        }
    }


    typedef void (*mallocErrHandler)();

    static mallocErrHandler handler;

public:
    static void* allocate(size_t n)
    {
#ifdef USE_DDEBUG
        cout << "mallocAlloc::  allocate" << endl;
#endif
        void* result = malloc(n);
        if(result==NULL)
            result = malloc_doerr(n);
        return result;
    }

    static void deallocate(void* p)
    {
#ifdef USE_DDEBUG
        cout << "mallocAlloc::  deallocate" << endl;
#endif
        free(p);
    }


    static void* reallocate(void* p, size_t newsz)
    {
#ifdef USE_DDEBUG
        cout << "mallocAlloc::  reallocate" << endl;
#endif
        void* result = realloc(p, newsz);
        if(result==NULL)
            result = realloc_doerr(p, newsz);
        return result;
    }

    static mallocErrHandler setMallocErrHandler(mallocErrHandler newhandler)
    {
        mallocErrHandler old = handler;
        handler = newhandler;
        return old;
    }
};

class MemoryPoolAlloc
{
private:
    enum {ALIGN=8};
    enum {BYTESMAX=128};
    enum {FREELISTNUM=16};

    union Block
    {
        Block* next;
        char cliData[1];
    };

    static size_t raiseUp(size_t bytes)
    {
        return (bytes+ALIGN-1) & ~(ALIGN-1);
    }

private:
    static char*  startPool;
    static char*  endPool;
    static size_t poolSize;

    static Block* freeBlockList[FREELISTNUM];

    static size_t findPropelIndex(size_t bytes)
    {
        return bytes / ALIGN;
    }

    static void* refill(size_t size)
    {
#ifdef USE_DDEBUG
        cout << "MemoryPoolAlloc::  refill " << size << " bytes"<< endl;
#endif
        int nBlocks = 20;
        char* chunk = chunkAlloc(size, nBlocks);
        Block** myBlockList;
        Block* ret, *currentBlock, *nextBlock;

        if(nBlocks==1)
            return chunk;

        myBlockList = freeBlockList + findPropelIndex(size);

        ret = (Block*)chunk;

        *myBlockList = nextBlock = (Block*)(chunk+size);

        /*0 is returned to client*/
        for(int i=1; ; i++)
        {
            currentBlock = nextBlock;
            nextBlock = (Block*)((char*)nextBlock + size);
            if(nBlocks-1 == i)
            {
                currentBlock->next = NULL;
                break;
            }
            else
            {
                currentBlock->next = nextBlock;
            }
        }
        return ret;
    }

    static char* chunkAlloc(size_t size, int& nblocks)
    {
#ifdef USE_DDEBUG
        cout << "MemoryPoolAlloc::  chunkAlloc " << size << " bytes" << endl;
#endif
        char* ret;
        size_t neededBytes = size * nblocks;
        size_t leftBytes = endPool - startPool;
#ifdef USE_DDEBUG
        cout << "chunkAlloc::   neededBytes = " << neededBytes << ", leftBytes = " << leftBytes << endl;
#endif
        if( leftBytes >= neededBytes)
        {
#ifdef USE_DDEBUG
            cout << "chunkAlloc::   leftBytes>=neededBytes" << endl;
#endif
            ret = startPool;
            startPool = startPool + neededBytes;
            return ret;
        }
        else if( leftBytes >= size )
        {
#ifdef USE_DDEBUG
            cout << "chunkAlloc::   leftBytes>=oneBlockSize" << endl;
#endif
            nblocks = leftBytes/size;
            neededBytes = size * nblocks;
            ret = startPool;
            startPool = startPool + neededBytes;
            return ret;
        }
        else
        {
            size_t bytesToGet = 2 * neededBytes + raiseUp(poolSize>>4);
#ifdef USE_DDEBUG
            cout << "chunkAlloc::   left bytes can not supply one block,bytesToGet = "
                 << bytesToGet << endl;
#endif
            // try to make use of the left-over piece
            if(leftBytes>0)
            {
#ifdef USE_DDEBUG
                cout << "chunkAlloc::   left bytes can not supply one block, leftBytes = "
                     << leftBytes << endl;
#endif
                Block** myBlockList  =  freeBlockList + findPropelIndex(leftBytes);
                /*adjust freeBlockList, enroll the left-over piece*/
                ((Block*)startPool)->next = *myBlockList;
                *myBlockList = (Block*)startPool;
            }

            startPool = (char*)malloc(bytesToGet);   //????

            /*heap memory is run out*/
            if(startPool==NULL)
            {
               Block** myBlockList, *pointer;

               for(int i=size; i<BYTESMAX; i+=ALIGN)
               {
                   myBlockList = freeBlockList + findPropelIndex(i);
                   pointer = *myBlockList;
                   if(pointer!=NULL)
                   {
                       *myBlockList = pointer->next;
                       startPool = (char*)pointer;
                       endPool = startPool + i;
                       return chunkAlloc(size, nblocks);
                   }
               }
               /*nothing left*/
               endPool = NULL;// exception
               startPool = (char*)mallocAlloc::allocate(bytesToGet);
            }
            poolSize = poolSize + bytesToGet;
#ifdef USE_DDEBUG
            cout << "chunkAlloc::   poolSize changed: " << poolSize << endl;
#endif
            endPool = startPool + bytesToGet;

            return chunkAlloc(size, nblocks);
        }
    }

public:
    static void* allocate(size_t n)
    {
#ifdef USE_DDEBUG
        cout << "MemoryPoolAlloc::  allocate size " << n << " bytes" << endl;
#endif
        Block** myBlockList;
        Block* ret;

        if(n > BYTESMAX) //? signed to unsigned
        {
#ifdef USE_DDEBUG
            cout << "mallocAlloc::  allocate allocated size:" << n << endl;
#endif
            return mallocAlloc::allocate(n);
        }

        myBlockList = freeBlockList + findPropelIndex(n);
        ret = *myBlockList;

        /*did not find the propel Block, refill the free Block list.*/
        if(ret==NULL){
            void* addr = refill(raiseUp(n));
            return addr;
        }

        /*find the propel, adjust freeBlockList*/
        *myBlockList = ret->next;

        return ret;
    }

    static void* reallocate(void* addr, size_t odsz, size_t newsz)
    {
#ifdef USE_DDEBUG
        cout << "MemoryPoolAlloc::  reallocate(" << addr << ", " << odsz << " ," << newsz << ")" << endl;
#endif
        void* ret;

        if( (odsz>BYTESMAX) && (newsz>BYTESMAX) )
            return realloc(addr, newsz);
        if(raiseUp(odsz) == raiseUp(newsz))
            return addr;
        ret = allocate(newsz);
        memcpy(ret, addr, (newsz>odsz) ? odsz : newsz);
        deallocate(addr, odsz);

        return ret;
    }

    static void  deallocate(void* addr, size_t n)
    {
#ifdef USE_DDEBUG
        cout << "MemoryPoolAlloc::  deallocate " << addr <<" " <<  n << " bytes" << endl;
#endif
        Block* obj = (Block*)addr;
        Block** myBlockList;

        if(n > BYTESMAX)
        {
#ifdef USE_DDEBUG
            cout << "deallocate::   use c free " << addr << " " << n << " bytes" << endl;
#endif
            mallocAlloc::deallocate(addr);
            return;
        }
        myBlockList = freeBlockList + findPropelIndex(n);
        obj->next = *myBlockList;
        *myBlockList = obj;
    }

};

template<class T, class Alloc>
class standardAlloc
{
public:
    static T* allocate(size_t n)
    {
        return (n==0) ? NULL : (T*)Alloc::allocate(n*sizeof(T));
    }
    static T* allocate(void)
    {
        return (T*)Alloc::allocate(sizeof(T));
    }
    static void dealloate(T* p, size_t n)
    {
        if(n!=0)
            Alloc::deallocate(p, n*sizeof(T));
    }
    static void deallocate(T* p)
    {
        Alloc::deallocate(p, sizeof(T));
    }
};



typedef MemoryPoolAlloc poolAlloc;


} /*namespace DLib*/

#endif // ALLOC_H
