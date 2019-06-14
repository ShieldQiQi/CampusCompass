#ifndef DOUBLELINKLIST_H
#define DOUBLELINKLIST_H

/*
基于C++template实现的双向链表类
Author：SHIELD_QI
时间：2018/06/06
*********************************************/

//--------------------------节点结构---------------------------/
template <typename T>
class Node
{
public:
    T value;
    Node* next;
    Node* prior;
public:
    Node()=default;
    Node(T value,Node* next,Node* prior)
        :value(value),next(next),prior(prior){}
};
//--------------------------双链表---------------------------/
template <typename T>
class DoubleLink
{
public:
    typedef Node<T>* pointer;
    DoubleLink();
    ~DoubleLink();

    int size();                       //获取长度
    bool isEmpty();                   //判断链表是否为空
    bool DestroyList();               //销毁顺序线性表

    int LocateElem(T t);              //定位元素位置

    Node<T>* insert(int index,T t);   //在位置index处插入元素t
    Node<T>* insert_head(T t);        //在链表头插入
    Node<T>* insert_last(T t);        //在链表尾插入

    Node<T>* del(int index);          //指定位置删除元素
    Node<T>* delete_head();           //删除链表头
    Node<T>* delete_last();           //删除链表尾

    Node<T>* get_PriorElem(int index);//获取前驱节点
    Node<T>* get_NextElem(int index); //获取后继节点

    Node<T>* getHead();               //获取链表头部节点

    Node<T>* getNode(int index);      //获取指定位置节点

    void ListTraverse();              //遍历双链表

    void Union(DoubleLink<T> &L);     //合并线性表

    //合并两个按值递增的有序线性表到另一个线性表
    void MergeList(DoubleLink<T> &L1,DoubleLink<T> &L2);

//    //" = "运算符重载
//    DoubleLink<T>& operator=(const DoubleLink<T> &link);

    int count;
    Node<T>* phead;                   //头节点指针

};
//--------------------默认构造函数------------------/
template <typename T>
DoubleLink<T>::DoubleLink()
    :count(0),phead(nullptr)
{
    phead=new Node<T>();             //创建头节点
    phead->next=nullptr;
    phead->prior=nullptr;
}
//----------------------析构函数-------------------/
template <typename T>
DoubleLink<T>::~DoubleLink()
{
    Node<T>* pNode =phead->next;
    while(pNode!=nullptr)
    {
        Node<T>* temp=pNode;
        pNode=pNode->next;
        delete temp;                //销毁节点
    }
}
//-----------------返回指定位置前一个的节点---------------/
template <typename T>
Node<T>* DoubleLink<T>::getNode(int index)
{
    if(index<0||index>count)        //如果不在范围内、返回空指针
        return nullptr;

    int temp=0;
    Node<T>* Node=phead;
    while(temp<index)
    {
        temp++;
        Node=Node->next;
    }
    return Node;
}
//----------------------获取前驱节点-------------------/
template <typename T>
Node<T>* DoubleLink<T>::get_PriorElem(int index)
{
    return getNode(index);
}
//----------------------获取后继节点-------------------/
template <typename T>
Node<T>* DoubleLink<T>::get_NextElem(int index)
{
    Node<T>* temp=getNode(index);
    return (temp->next)->next;
}
//-----------------返回链表的大小---------------/
template <typename T>
int DoubleLink<T>::size()
{
    return count;
}
//-----------------判断链表为空---------------/
template <typename T>
bool DoubleLink<T>::isEmpty()
{
    return count==0;           //count为0、则返回0、表示空
}
//-----------------销毁顺序表---------------/
template <typename T>
bool DoubleLink<T>::DestroyList()
{
    Node<T>* pNode =phead->next;
    while(pNode!=nullptr)
    {
        Node<T>* temp=pNode;
        pNode=pNode->next;
        delete temp;             //销毁节点
    }
    phead->next=nullptr;
    count=0;
    return count==0;           //count为0、则返回0、表示空
}
//-----------------定位元素---------------/
template <typename T>
int DoubleLink<T>::LocateElem(T t)
{
    Node<T>* temp=phead;
    int i=1;
    while(temp!=nullptr)
    {
        i++;
        if(temp->value==t)
            return i;
        temp=temp->next;
    }
    return 0;
}
//-----------------获取头节点---------------/
template <typename T>
Node<T>* DoubleLink<T>::getHead()
{
    return phead->next;
}
//-------------在指定位置插入新节点-----------/
template <typename T>
Node<T>* DoubleLink<T>::insert(int index, T t)
{
    Node<T>* preNode=getNode(index);
    if(preNode)
    {
        //构造新节点、指向下一个节点、指向上一个节点
        Node<T>* newNode=new Node<T>(t,preNode->next,preNode);
        //原先的节点指向当前节点
        preNode->next=newNode;
        preNode->next->prior=newNode;
        //长度加一
        count++;
        //std::cout<<"*"<<std::endl;
        return newNode;
    }
    return nullptr;
}
//----------------在头部插入新节点--------------/
template <typename T>
Node<T>* DoubleLink<T>::insert_head(T t)
{
    phead=new Node<T>;
    phead->value=t;
    return phead;
}
//----------------在尾部插入新节点--------------/
template <typename T>
Node<T>* DoubleLink<T>::insert_last(T t)
{
    return insert(count,t);
}
//---------------删除指定位置元素--------------/
template <typename T>
Node<T>* DoubleLink<T>::del(int index)
{
    if(isEmpty())
        return nullptr;
    Node<T>* ptrNode=getNode(index);
    Node<T>* delNode=ptrNode->next;
    ptrNode->next=delNode->next;
    delNode->next->prior=ptrNode;
    count--;
    delete delNode;
    return ptrNode->next;
}
//-----------------删除头节点-----------------/
template <typename T>
Node<T>* DoubleLink<T>::delete_head()
{
    return del(0);
}
//-----------------删除尾节点-----------------/
template <typename T>
Node<T>* DoubleLink<T>::delete_last()
{
    return del(count);
}
//-----------------遍历双链表-----------------/
template <typename T>
void DoubleLink<T>::ListTraverse()
{
    DoubleLink<int>::pointer ptr=this->getHead();
    while(ptr!=nullptr)
    {
        std::cout<<ptr->value<<endl;
        ptr=ptr->next;
    }
}
//-----------------合并线性表-----------------/
template <typename T>
void DoubleLink<T>::Union(DoubleLink<T> &L)
{
    Node<T>* temp=L.getHead();
    while(temp!=nullptr)
    {
        if(LocateElem(temp->value)==0)
        {
            insert(count,temp->value);
//            std::cout<<count<<endl;
        }
        temp=(temp->next);
    }
}
//-------------合并有序的两个线性表------------/
template <typename T>
void DoubleLink<T>:: MergeList(DoubleLink<T> &L1,DoubleLink<T> &L2)
{
    Node<T>* link1=L1.getHead();
    Node<T>* link2=L2.getHead();

    while(link1!=nullptr&&link2!=nullptr)
    {
        if(link1->value<=link2->value)
        {
           insert_last(link1->value);
            link1=link1->next;
        }else
        {
            insert_last(link2->value);
            link2=link2->next;
        }
    }
    while(link1!=nullptr)
    {
       insert_last(link1->value);
       link1=link1->next;
       ListTraverse();
    }
    while(link2!=nullptr)
    {
       insert_last(link2->value);
       link2=link2->next;
    }
}





#endif // DOUBLELINKLIST_H
