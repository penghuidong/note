#ifndef DSINGLELINKLIST_H
#define DSINGLELINKLIST_H

#include "DList.h"
#include "DObject.h"

namespace DLib {

template<typename T>
class ListNode
{
public:
    typedef ListNode<T>* nodepointer;

    T value;
    ListNode* next;
    ListNode() : next(NULL) {}
    ~ListNode(){
        next = NULL;
    }
};


template<typename T>
class DSingleLinkList : public DList<T>
{
private:
    typedef ListNode<T>* nodepointer;
    size_t m_length;

    class m_header
    {
    public:
        char reserve[sizeof(T)];
        nodepointer next;
        m_header() : next(NULL){}
    };
    m_header header;

    nodepointer m_current;

private:
    nodepointer createNode(const T val){
         //allocate raw memory
        nodepointer ret = static_cast<nodepointer>(DObject<>::operator new(sizeof(ListNode<T>)));
        if(ret!=NULL){
            ret = ::new (ret) ListNode<T>;  //construct object
            ret->next = NULL;
            ret->value = val;
        }
        return ret;
    }

    void destroyNode(ListNode<T>* node){
        if(node==header.next){
            header.next = header.next->next;
            m_length--;
            (&(node->value))->~T();
            DObject<>::operator delete(node);
        }else {
            ListNode<T>* prev = getPrevious(node);
            prev->next = node->next;
            m_length--;
            (&(node->value))->~T();
            DObject<>::operator delete(node);
        }
    }

    void destroyNode(ListNode<T>* first, ListNode<T>* last){
        ListNode<T>* current = first;
        ListNode<T>* end = last->next;
        while (current!=end) {
            ListNode<T>* toDel = current;
            current = current->next;
            destroyNode(toDel);
        }
    }

    ListNode<T>* makeLink(ListNode<T>* prev, ListNode<T>* newnode){
        if(prev!=NULL){
            newnode->next = prev->next;
            prev->next = newnode;
        }
        return newnode;
    }

    void fill(size_t n, const T& val){
        header.next = createNode(val);
        ListNode<T>* pointer = header.next;
        for(size_t i=1; i<n; i++)
            pointer = makeLink(pointer, createNode(val));
    }

private:
    const ListNode<T>* getPrevious(size_t index) const
    {
        ListNode<T>* ret = NULL;
        if(index==0)
            ret = reinterpret_cast<ListNode<T>*>(&header);
        else if(index>0){
            ListNode<T>* temp = header.next;
            for(size_t i=0; i<index; i++)
                temp = temp->next;
            ret = temp;
        }
        return ret;
    }
    ListNode<T>* getPrevious(size_t index)
    {
        ListNode<T>* ret = NULL;
        if(index==0)
            ret = reinterpret_cast<ListNode<T>*>(&header);
        else if(index>0){
            ListNode<T>* temp = header.next;
            for(size_t i=1; i<index; i++)
                temp = temp->next;
            ret = temp;
        }
        return ret;
    }

    ListNode<T>* getPrevious(ListNode<T>* node){
        ListNode<T>* prev = header.next;
        while(prev->next!=node)
            prev = prev->next;
        return prev;
    }

    ListNode<T>* getNodePosition(size_t index)
    {
        ListNode<T>* ret = NULL;
        if(index==0)
        {
            if(header.next!=NULL)
                ret = header.next;
        }
        else if(index>0)
        {
            if(header.next)
            {
                ListNode<T>* temp = header.next;
                for(size_t i=0; i<index; i++)
                    temp = temp->next;
                ret = temp;
            }
        }
        return ret;
    }

    const ListNode<T>* getNodePosition(size_t index) const
    {
        ListNode<T>* ret = NULL;
        if(index==0)
        {
            if(header.next!=NULL)
                ret = header.next;
        }
        else if(index>0)
        {
            if(header.next)
            {
                ListNode<T>* temp = header.next;
                for(size_t i=0; i<index; i++)
                    temp = temp->next;
                ret = temp;
            }
        }
        return ret;
    }


public:
    DSingleLinkList() : m_length(0){
        header.next = NULL;
    }

    explicit DSingleLinkList(size_t num): m_length(num) {
        fill(num, T());
    }

    DSingleLinkList(size_t num, const T& val) : m_length(num) {
        fill(num, val);
    }

    bool insert(size_t index, const T& val)
    {
        bool ret = (0<=index );
        if(ret){
            ListNode<T>* prev = getPrevious(index);
            makeLink(prev, createNode(val));
            m_length++;
        }
        return ret;
    }

    bool pushBack(const T& val)
    {
        bool ret = false;
        if(m_length!=0)
            ret = insert(m_length, val);
        if(m_length==0)
            ret = insert(0, val);
        return ret;
    }

    T remove(size_t index)
    {
        T ret;
        if(0<=index && index<m_length){
            ListNode<T>* toDel = getNodePosition(index);
            ret = toDel->value;
            destroyNode(toDel);
        }
        return ret;
    }


    bool set(size_t index, const T& val)
    {
        bool ret = (0<=index && index<m_length);
        if(ret){
            ListNode<T>* currentNode = getNodePosition(index);
            if(currentNode!=NULL)
                currentNode->value = val;
        }
        return ret;
    }

    size_t find(const T& val) const
    {
        size_t ret=-1;  //error code have to indicate
        for(size_t i=0; i<m_length; i++){
            if(getNodePosition(i)->value==val){
                ret = i; break;
            }
        }
        return ret;
    }
    bool get(size_t index, T& val) const
    {
        bool ret = (0<=index && index<m_length);
        if(ret){
            const ListNode<T>* currentNode = getNodePosition(index);
            if(currentNode!=NULL)
                val = currentNode->value;
        }
        return true;
    }
    size_t length() const
    {
        return m_length;
    }
    void clear()
    {
        destroyNode(getNodePosition(0), getNodePosition(m_length-1));
        m_length = 0;
    }

    ~DSingleLinkList()
    {
        if(m_length!=0){
            clear();
            m_length = 0;
            header.next = NULL;
        }
    }
public:
    T& operator[](size_t index){
        return getNodePosition(index)->value;
    }
};

}/*namespace std*/
#endif // DSINGLELINKLIST_H
