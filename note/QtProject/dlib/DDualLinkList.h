#ifndef DDUALLINKLIST_H
#define DDUALLINKLIST_H


#include "DList.h"

namespace DLib {

template<typename T>
class DualNode
{
public:
    T value;
    DualNode* prev;
    DualNode* next;

    DualNode() : next(NULL),prev(NULL) {}
    ~DualNode(){
        next = NULL;
        prev = NULL;
    }
};


template<typename T>
class DDualLinkList : public DList<T>
{
private:
    size_t m_length;
    class m_header
    {
    public:
        char reserve[sizeof(T)];
        DualNode<T>* prev;
        DualNode<T>* next;
        m_header() : prev(NULL),next(NULL){}
    };
    m_header header;

private:
    DualNode<T>* createNode(const T& val){
        DualNode<T>* newnode = static_cast<DualNode<T>*>( DObject<>::operator new(sizeof(DualNode<T>)));
        if(newnode!=NULL){
            newnode = ::new (newnode) DualNode<T>;
            newnode->value = val;
            newnode->next = newnode->prev = NULL;
        }
        return newnode;
    }

    void destoryNode(DualNode<T>* toDel){
        DualNode<T>* nextnode = toDel->next;
        if(toDel==header.next){
            header.next = nextnode;
            m_length--;
            (&(toDel->value))->~T();
            DObject<>::operator delete(toDel);
        }else {
            DualNode<T>* prenode = toDel->prev;
            prenode->next = nextnode;
            nextnode->prev = prenode;
            m_length--;
            (&(toDel->value))->~T();
            DObject<>::operator delete(toDel);
        }
    }

    void destoryNode(DualNode<T>* first, DualNode<T>* last){
        DualNode<T>* end = last->next;
        DualNode<T>* current = first;
        while(current!=end){
            DualNode<T>* toDel = current;
            current = current->next;
            destoryNode(toDel);
        }
    }

    DualNode<T>* makeLink(DualNode<T>* prevnode, DualNode<T>* newnode){
        if(prevnode->next==NULL){
            newnode->prev = prevnode;
            prevnode->next = newnode;
        } else if (prevnode->next!=NULL){
            newnode->next = prevnode->next;
            newnode->prev = prevnode;
            prevnode->next->prev = newnode;
            prevnode->next = newnode;
        }
        return newnode;
    }

    void fill(size_t num, const T& val){
        header.next = createNode(val);
        header.next->prev = reinterpret_cast<DualNode<T>*>(&header);
        DualNode<T>* pointer = header.next;
        for(size_t i=1; i<num; i++)
            pointer = makeLink(pointer, createNode(val));
    }

private:
    DualNode<T>* getNodePosition(size_t index){
        if(0<=index && index<m_length){
            DualNode<T>* ret = header.next;
            for(size_t i=0; i<index && index!=0; i++)
                ret = ret->next;
            return ret;
        }
    }

    const DualNode<T>* getNodePosition(size_t index) const {
        DualNode<T>* ret = header.next;
        for(size_t i=0; i<index && index!=0; i++)
            ret = ret->next;
        return ret;
    }

public:
    DDualLinkList() : m_length(0) {}

    DDualLinkList(size_t num) : m_length(num) {fill(num, T());}

    DDualLinkList(size_t num, const T& val) : m_length(num){fill(num,T(val));}

    bool insert(size_t index, const T& val){
        bool ret = 0<=index && index<m_length;
        if(ret){
            DualNode<T>* position = getNodePosition(index);
            DualNode<T>* newnode = createNode(val);
            makeLink(position, newnode);
            m_length++;
        }
        return ret;
    }

    bool remove(size_t index){
        bool ret = 0<=index && index<m_length;
        if(ret){
            DualNode<T>* toDel = getNodePosition(index);
            destoryNode(toDel);
        }

        return ret;
    }

    bool set(size_t index, const T& val){
        bool ret = 0<=index && index<m_length;
        if(ret){
            DualNode<T>* node = getNodePosition(index);
            node->value = val;
        }
        return ret;
    }

    bool get(size_t index, T& val) const{
        bool ret = 0<=index && index<m_length;
        if(ret){
            const DualNode<T>* node = getNodePosition(index);
            val = node->value;
        }
        return ret;
    }

    size_t find(const T& val) const
    {
        for(size_t i=0; i<m_length; i++){
            if(getNodePosition(i)->value==val)
                return i;
        }
        return -1;
    }
    size_t length() const{
        return m_length;
    }
    void clear(){
        destoryNode(getNodePosition(0), getNodePosition(m_length-1));
        m_length = 0;
    }
    ~DDualLinkList(){
        clear();
        header.next = NULL;
    }
public:
    T& operator[](size_t i){return getNodePosition(i)->value; }

};

}/*namespace DLib*/


#endif // DDUALLINKLIST_H
