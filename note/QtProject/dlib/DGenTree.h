#ifndef DGENTREE_H
#define DGENTREE_H

#include "DObject.h"
#include "DSingleLinkList.h"
#include "Config.h"
#include "DException.h"
#include "DQueue.h"
#include "DSharedPointer.h"
#include "DVector.h"

namespace DLib
{

template <typename T>
class DGenTreeNode
{
public:
    DSingleLinkList<DGenTreeNode<T>*> child;
    T nodeValue;
    DGenTreeNode<T>* parent;
    bool new_flag;

protected:
    DGenTreeNode(const DGenTreeNode<T>& );

    DGenTreeNode<T>& operator=(const DGenTreeNode<T>&);

    void* operator new(size_t size) throw()
    {
        return ::operator new(size);
    }

public:
    DGenTreeNode() : nodeValue(T()),parent(NULL), new_flag(false){}

    DGenTreeNode(const T& val) : nodeValue(val),parent(NULL),new_flag(false) {}

    static DGenTreeNode<T>* newNode(const T& val)
    {
        DGenTreeNode<T>* newnode = new DGenTreeNode<T>(val);
        if(newnode!=NULL)
            newnode->new_flag = true;
        return newnode;
    }
};

template <typename T>
class DGenTree : public DObject<>
{
private:
    DGenTreeNode<T>* m_root;
    DVector<T> levelTraveseData;
private:
    DGenTreeNode<T>* find_recursive(const T& val, DGenTreeNode<T>* list) const
    {
        DGenTreeNode<T>* ret = NULL;
        if(m_root!=NULL)
        {
            if(list->nodeValue == val)
                ret = list;
            else
                for(size_t i=0; i<list->child.length() && ret==NULL; i++)
                   ret = find_recursive(val,list->child[i]);
        }
        else
            throw_exception(invalidOperation, "DGTree is empty");
        return ret;
    }

    DGenTreeNode<T>* find_recursive(const DGenTreeNode<T>* node, DGenTreeNode<T>* list) const
    {
        DGenTreeNode<T>* ret = NULL;
        if(m_root!=NULL)
        {
            if(list==node)
                ret = list;
            else
                for(size_t i=0; i<list->child.length() && ret==NULL; i++)
                    ret = find_recursive(node, list);
        }
        else
            throw_exception(invalidOperation, "DGTree is empty");
        return ret;
    }

    void clear(DGenTreeNode<T>* node)
    {
        if(node!=NULL)
        {
            for(size_t i=0; i<node->child.length(); i++)
                clear(node->child[i]);
            if(node->new_flag==true) //delete node if is heap memory
                ::delete node;
        }
    }

    size_t countNode(DGenTreeNode<T>* node) const
    {
        size_t ret = 0;
        if(node!=NULL)
        {
            ret = 1;
            for(size_t i=0; i<node->child.length(); i++)
                ret += countNode(node->child[i]);
        }
        return ret;
    }

    size_t height(DGenTreeNode<T>* node) const
    {
        size_t ret = 0;
        if(node!=NULL)
        {
            for(size_t i=0; i<node->child.length(); i++)
            {
                size_t h = height(node->child[i]);
                if(ret<h)
                    ret = h;
            }
            ret +=1;
        }
        return ret;
    }

    size_t nodeDegree(DGenTreeNode<T>* node) const
    {
        size_t ret = 0;
        if(node!=NULL)
        {
            ret = node->child.length();
            for(size_t i=0; i<node->child.length(); i++)
            {
                size_t d = nodeDegree(node->child[i]);
                if(ret<d)
                    ret = d;
            }
        }
        return ret;
    }

public :
    DGenTree() : m_root(NULL) {}

    DGenTreeNode<T>* find(DGenTreeNode<T>* list,const T& val) const
    {
        return find_recursive(val, list);
    }

    DGenTreeNode<T>* find(DGenTreeNode<T>* list,DGenTreeNode<T>* node ) const
    {
        return find_recursive(node, list);
    }

    DGenTreeNode<T>* find(const T& val) const
    {
        return find(root(), val);
    }

    bool insert(DGenTreeNode<T>* node)
    {
        bool checkCondition = (node!=NULL);
        if(checkCondition)
        {
            if(m_root!=NULL){
                DGenTreeNode<T>* parent = find_recursive(node, m_root);
                if(parent!=NULL && parent->child.find(node)==size_t(-1))
                    parent->child.pushBack(node);
            }else if(m_root==NULL){
                node->parent = NULL;
                m_root = node;
            }
        }else
            throw_exception(invalidParameter,"parameter is NULL");
        return checkCondition;
    }

    bool insert(DGenTreeNode<T>* parent, const T& val)
    {
        bool checkCondition = (parent!=NULL);
        if(checkCondition){
            DGenTreeNode<T>* node = DGenTreeNode<T>::newNode(val);
            node->parent = parent;
            parent->child.pushBack(node);
        }
        return checkCondition;
    }

    DSharedPointer<DGenTree<T>> removeNodeAndChild(DGenTreeNode<T>* node)
    {
        DGenTree<T>* ret = NULL;
        node = find(node);
        if(node!=NULL)
        {
            ret = new DGenTree<T>();
            if(ret!=NULL)
            {
                if(this->root()==node)
                {
                    ret = this->m_root;
                    this->m_root = NULL;
                }
                else
                {
                    DSingleLinkList<DGenTreeNode<T>*> childlist = node->parent->child;
                    childlist.remove(childlist.find(node));
                    node->parent = NULL;
                }
                ret->m_root = node;
            }
        }
        else
            throw_exception(invalidParameter, "can't remove NULL node");
        return ret;
    }

    DSharedPointer<DGenTree<T>> removeNodeAndChild(const T& val)
    {
        DGenTree<T>* ret = NULL;
        DGenTreeNode<T>* node = find(val);
        if(node!=NULL)
        {
            ret = new DGenTree<T>();
            if(ret!=NULL)
            {
                if(this->root()==node)
                {
                    ret->m_root = this->m_root;
                    this->m_root = NULL;
                }
                else
                {
                    DSingleLinkList<DGenTreeNode<T>*>* childlist = &(node->parent->child);
                    childlist->remove(childlist->find(node));
                    node->parent = NULL;
                }
                ret->m_root = node;
            }
        }
        return ret;
    }

    bool levelTravese()
    {
        bool ret = m_root!=NULL;
        if(ret)
        {
            levelTraveseData.clear();
            DQueue<DGenTreeNode<T>*> tempQueue;
            tempQueue.push(root());
            while(tempQueue.length()>0)
            {
                DGenTreeNode<T>* node = tempQueue.pop();
                levelTraveseData.pushBack(node->nodeValue);
                for(size_t i=0; i<node->child.length(); i++)
                    tempQueue.push(node->child[i]);
            }
        }
        return ret;
    }

    DVector<T>& getTravese()
    {
        return levelTraveseData;
    }

    inline DGenTreeNode<T>* root() const {return m_root;}

    size_t count() const {return countNode(root());}

    size_t height() const {return height(root());}

    size_t degree() const {return nodeDegree(root());}

    ~DGenTree()
    {
        clear(root());
    }
};

}



#endif // DGENTREE_H
