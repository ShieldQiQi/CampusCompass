/*
 * 基于链表的队列实现
 * Author:SHIELD_QI
 * Date:2018-06-07
 * ********************************************/

#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <iostream>
using namespace std;

//---------------------创建节点类-----------------------/
template <typename T>
class QueueNode
{
public:
    QueueNode(T t):value(t),next(nullptr){}
    QueueNode()=default;
    T value;
    QueueNode<T>* next;

};
//------------------构建队列ADT数据类-------------------/
template <typename T>
class LinkQueue
{
public:
    LinkQueue();
    ~LinkQueue();
public:
    bool isEmpty();         //判断是否为空
    int getSize();          //获取队列大小
    bool pop();             //出队列
    void push(T t);         //进队列
    T getFront();           //获取队列头元素
    void QueueTravers();    //遍历队列
    void DestoryQueue();    //销毁队列
    void ClearQueue();      //清空队列
private:
    int count;              //队列元素个数
    QueueNode<T>* phead;         //队列头
    QueueNode<T>* pend;          //队列尾
};

//----------------构造函数-----------------/
template <typename T>
LinkQueue<T>::LinkQueue():count(0)
{
    phead=new QueueNode<T>();
    pend=new QueueNode<T>();
    pend=phead;
}
//----------------析构函数-----------------/
template <typename T>
LinkQueue<T>::~LinkQueue()
{
    while(phead->next!=nullptr)
    {
        QueueNode<T>* pQueueNode=phead->next;
        phead->next=pQueueNode->next;
        delete pQueueNode;
    }
}
//---------------判断是否为空---------------/
template <typename T>
bool LinkQueue<T>::isEmpty()
{
    return count==0;
}
//---------------获取队列大小---------------/
template <typename T>
int LinkQueue<T>::getSize()
{
    return count;
}
//------------进队列：从队尾插入-------------/
template <typename T>
void LinkQueue<T>::push(T t)
{
    QueueNode<T>* pQueueNode=new QueueNode<T>(t);
    pend->next=pQueueNode;
    pend=pQueueNode;
    count++;
}
//------------出队列：从队首弹出-------------/
template <typename T>
bool LinkQueue<T>::pop()
{
    if(count==0)
        return false;
    QueueNode<T>* pQueueNode=phead->next;
    phead->next=phead->next->next;
    if(phead->next!=pend)
    {
        pend=phead;
    }
    delete pQueueNode;
    count--;
    return true;
}
//-------------获取队首元素---------------/
template <typename T>
T LinkQueue<T>::getFront()
{
    return phead->next->value;
}
//---------------遍历队列---------------/
template <typename T>
void LinkQueue<T>::QueueTravers()
{
    QueueNode<T>* pQueueNode=new QueueNode<T>();
    pQueueNode=phead->next;
    while(pQueueNode!=nullptr)
    {
        std::cout<<pQueueNode->value<<endl;
        pQueueNode=pQueueNode->next;
    }
}
//---------------销毁队列---------------/
template <typename T>
void LinkQueue<T>::DestoryQueue()
{
    while(phead->next!=nullptr)
    {
        QueueNode<T>* pQueueNode=phead->next;
        phead->next=phead->next->next;
        delete pQueueNode;
    }
    phead=nullptr;
}
//---------------清空队列---------------/
template <typename T>
void LinkQueue<T>::ClearQueue()
{
    while(phead->next!=nullptr)
    {
        QueueNode<T>* pQueueNode=phead->next;
        phead->next=phead->next->next;
        delete pQueueNode;
    }
}




















#endif // LINKQUEUE_H
