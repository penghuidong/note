#ifndef DBINTREE_H
#define DBINTREE_H

#include "DException.h"
#include "DObject.h"
#include "DSingleLinkList.h"
#include "DSharedPointer.h"
#include "Config.h"

namespace DLib
{

template <typename T>
class DBinTreeNode
{
public:
    T nodeValue;
    DBinTreeNode<T>* m_parent;
    DBinTreeNode<T>* rchild;
    DBinTreeNode<T>* lchild;

    bool newFlag;

    void* operator new(size_t size)
    {
        return DObject<>::operator new(size);
    }

    DBinTreeNode(const DBinTreeNode& rval) : m_parent(NULL), rchild(NULL), lchild(NULL), newFlag(false) {}

    DBinTreeNode& operator =(const DBinTreeNode& rval);

public:
    DBinTreeNode() : m_parent(NULL), rchild(NULL), lchild(NULL), newFlag(false) {}

    DBinTreeNode(const T& val) : nodeValue(val), m_parent(NULL), rchild(NULL), lchild(NULL), newFlag(false) {}

    static DBinTreeNode* newNode(const T& val)
    {
        DBinTreeNode* ret = NULL;
        ret = static_cast<DBinTreeNode*>(DObject<>::operator new(sizeof(DBinTreeNode)));
        if(ret!=NULL)
        {
            ::new (ret) DBinTreeNode(val);
            ret->newFlag = true;
        }
        return ret;
    }

    bool getNewFlag() const {return newFlag;}
};


template <typename T>
class DBinTree : public DObject<>
{
private:
    DBinTreeNode<T>* m_root;

public:
    enum DBinTreeNodePos
    {
        ANY,
        LEFT,
        RIGHT
    };

private:
    DBinTreeNode<T>* find_recursive(DBinTreeNode<T>* tree, DBinTreeNode<T>* node) const
    {
        DBinTreeNode<T>* ret = NULL;
        if(node==tree)
            ret = node;
        else
        {
            if(tree!=NULL)
            {
                if(ret==NULL)
                    ret = find_recursive(tree->lchild, node);
                if(ret==NULL)
                    ret = find_recursive(tree->rchild, node);
            }
        }
        return ret;
    }

    DBinTreeNode<T>* find_recursive(DBinTreeNode<T>* node, const T& val) const
    {
        DBinTreeNode<T>* ret = NULL;
        if(node->nodeValue == val)
            ret = node;
        else
        {
            if(node!=NULL)
            {
                if(ret==NULL)
                    ret = find_recursive(node->lchild, val);
                if(ret==NULL)
                    ret = find_recursive(node->rchild, val);
            }
        }
        return ret;
    }

    bool insert_private(DBinTreeNode<T>* parent, DBinTreeNode<T>* node, DBinTreeNodePos pos)
    {
        bool ret = parent!=NULL;
        if(ret)
        {
            if(pos==ANY)
            {
                if(parent->lchild==NULL)
                    parent->lchild = node;
                else if(parent->rchild==NULL)
                    parent->rchild = node;
                else
                    ret = false;
            }
            else if(pos==LEFT)
            {
                if(parent->lchild==NULL)
                    parent->lchild = node;
                else
                    ret = false;
            }
            else{
                if(parent->rchild==NULL)
                    parent->rchild = node;
                else
                    ret = false;
            }
        }
        return ret;
    }

    void remove_private(DBinTreeNode<T>* node, DBinTree<T>*& rettree)
    {
        rettree = static_cast<DBinTree<T>*>(DObject<>::operator new(sizeof(DBinTree<T>)));
        if(rettree!=NULL)
        {
            if(root()==node)
                m_root = NULL;
            else
            {
                DBinTreeNode<T>* parent = node->m_parent;
                if(parent!=NULL)
                {
                    if(parent->lchild==node)
                        parent->lchild = NULL;
                    else if(parent->rchild==node)
                        parent->rchild = NULL;
                    node->m_parent = NULL;
                }
                rettree->m_root = node;
            }
        }
    }

    size_t count(DBinTreeNode<T>* node) const
    {
        size_t ret = 0;
        if(node!=NULL)
            ret = count(node->lchild) + count(node->rchild) + 1;
        return ret;
    }

    size_t height(DBinTreeNode<T>* node) const
    {
        size_t ret = 0;
        if(node!=NULL)
        {
            size_t lh = height(node->lchild);
            size_t rh = height(node->rchild);
            lh>rh ? ret=lh : ret=rh;
        }
        return ret;
    }
public:
    DBinTree(): m_root(NULL){}

    DBinTreeNode<T>* find(DBinTreeNode<T>* node) const {return find_recursive(root(), node);}

    DBinTreeNode<T>* find(const T& val) const {return find_recursive(root(), val);}

    DBinTreeNode<T>* root() const {return m_root;}

    size_t count() const {return count(root());}

    size_t height() const {return height(root());}



    bool insert(DBinTreeNode<T>* parent, const T& val, DBinTreeNodePos pos = ANY)
    {
        bool ret = parent!=NULL;
        if(ret)
        {
            if(find(parent)!=NULL){
                DBinTreeNode<T>* node = DBinTreeNode<T>::newNode(val);
                if(node!=NULL)
                {
                    node->m_parent = parent;
                    node->lchild = node->rchild = NULL;
                    ret = insert_private(parent, node, pos);
                }
            }
        }
        return ret;
    }

    bool insertRoot(const T& val)
    {
        bool ret = true;
        DBinTreeNode<T>* root = DBinTreeNode<T>::newNode(val);
        if(root!=NULL)
            m_root = root;
        else
            ret = false;
        return ret;
    }

    DSharedPointer<DBinTree<T>> remove(DBinTreeNode<T>* node)
    {
        DBinTree<T>* ret = NULL;
        node = find(node);
        if(node!=NULL)
            remove_private(node, ret);
        else
            throw_exception(invalidParameter, "tree have not node");
        return ret;
    }

    DSharedPointer<DBinTree<T>> remove(const T& val)
    {
        DBinTree<T>* ret = NULL;
        DBinTreeNode<T>* node = find(val);
        if(node!=NULL)
            remove_private(node, ret);
        else
            throw_exception(invalidParameter, "tree have not node");
        return ret;
    }




};



}


#endif // DBINTREE_H
