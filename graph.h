/*
 * Project:The ADT for Graph by adjacency list(undirection)
 * Date:2018-07-01
 * Author:SHIELD_QI
 * ********************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <string.h>
#include <iostream>
#include "linkqueue.h"

//-----------------------弧的类节点定义-----------------------/
class AdjListArcNode
{
public:
    int adjVex;                     // 该弧所指向的顶点的位置
    AdjListArcNode* nextArc;        // 指向下一条弧的指针
    float weight;                   //该弧权重
public:
    ~AdjListArcNode(){}
    AdjListArcNode(int _adjVex,AdjListArcNode* _nextArc,float _weight)
        :adjVex(_adjVex),nextArc(_nextArc),weight(_weight){}
};

//----------------------顶点的类节点定义----------------------/
template <typename T>
class AdjListVexNode
{
public:
    T name;                         //该节点信息
    AdjListArcNode* firstArc;       //指向第一条依附该节点的弧
public:
    ~AdjListVexNode(){}
    AdjListVexNode(){}
    AdjListVexNode(T _name,AdjListArcNode* _firstArc)
        :name(_name),firstArc(_firstArc){}
};

//-----------------------无向图的ADT-----------------------/
template <typename T>
class AdjListUndirGraph
{
public:
    int vexMaxNum;
    AdjListVexNode<T>* vexTable;       //顶点集
    int vexNum;
    int arcNum;
    bool *flag;
public:
    ~AdjListUndirGraph(){}
    AdjListUndirGraph()
    {
        vexNum=0;
        arcNum=0;
        vexMaxNum=100;
        vexTable=new AdjListVexNode<T>[vexMaxNum];
        flag=new bool[vexMaxNum];
        for(int i=0;i<vexMaxNum;i++)
            flag[i]=0;
    }
    AdjListUndirGraph(AdjListVexNode<T> *_vexTable,int _vexNum,int _vexMaxNum=100,int arcNum=0)
        :vexTable(_vexTable),vexNum(_vexNum),vexMaxNum(_vexMaxNum),arcNum(_arcNum)
    {
        vexTable=new AdjListVexNode<T>[vexMaxNum];
        flag=new bool[vexMaxNum];
        for(int i=0;i<vexMaxNum;i++)
            flag[i]=0;
    }

public:
    bool CreatGraph();              //建立图
    bool isEmpty();                 //判断是否为空
    bool DestroyGraph();            //销毁图
    bool InsertVex(T _name);        //插入节点
    int  LocateVex(T _name);        //定位节点
    bool DeleteVex(T _name);        //删除节点
    bool InsertArc(T _name1,T _name2,float _weight);   //插入弧
    bool DeleteArc(T _name1,T _name2,float _weight);   //删除弧
    bool DFS(int v);                     //深度优先搜索
    bool DFSTraverse();
//    bool DFSTraVErse(int v);
    bool BFS(int v);                     //广度优先搜索
    bool BFSTraverse();
};

//-----------------------------------类方法定义-----------------------------------/

//--------------------创建图--------------------/
template <typename T>
bool AdjListUndirGraph<T>::CreatGraph()
{
    vexTable[0]=new AdjListVexNode<T>("start",nullptr);
    return ture;
}

//--------------------判断为空-------------------/
template <typename T>
bool AdjListUndirGraph<T>::isEmpty()
{
    return vexNum==0;
}

//--------------------销毁图--------------------/
template <typename T>
bool AdjListUndirGraph<T>::DestroyGraph()
{
    if(!isEmpty())
        return (delete[] vexTable);
}

//-------------------插入节点-------------------/

template <typename T>
bool AdjListUndirGraph<T>::InsertVex(T _name)
{
    AdjListVexNode<T>* a=vexTable+vexNum+1;
    a->name=_name;
    a->firstArc=NULL;
    vexNum++;
    //std::cout<<vexNum;
    return true;
}

//-------------------定位节点-------------------/

template <typename T>
int AdjListUndirGraph<T>::LocateVex(T _name)
{
    for(int i=1;i<=vexNum;i++)
    {
        if(vexTable[i].name==_name)
            return i;
    }
    return 0;
}

//-------------------删除节点-------------------/

template <typename T>
bool AdjListUndirGraph<T>::DeleteVex(T _name)
{
    int j=LocateVex(_name);
    if(j)
        return false;
    //删除以该节点为出度的弧
    AdjListArcNode* p=vexTable[j].firstArc,*q;
    while(p!=nullptr)
    {
        q=p;
        p=p->nextArc;
        delete q;
        arcNum--;
    }
    vexNum--;
    //定点前移
    for(int i=j;i<vexNum;i++)
    {
        vexTable[i]=vexTable[i+1];
    }
    //删除以该节点为入度的弧
    for(i=1;i<=vexNum;i++)
    {
        p=vexTable[i].firstArc;                          //指向该节点的第一条弧
        while(p)                                         //弧非空
        {
            if(p->adjVex==j)
            {
                if(p==vexTable[i].firstArc)              //待删节点是第一个节点
                {
                    vexTable[i].firstArc=p->nextArc;
                    delete p;
                    p=vexTable[i].firstArc;
                }else
                {
                    q->nextArc=p->nextArc;
                    delete p;
                    p=q->nextArc;                       //下面的else中已让q->nextArc=p
                }
            }
            else                                        //重新调整顶点节点位置
            {
                if(p->adjVex>j)
                    p->adjVex--;
                q=p;
                p=p->nextarc;
            }
        }

    }
    return ture;
}

//--------------------插入弧--------------------/

template <typename T>
bool AdjListUndirGraph<T>::InsertArc(T _name1,T _name2,float _weight)
{
    int i=LocateVex(_name1);
    int j=LocateVex(_name2);
    //如果不存在这两个节点、返回错误
    if(i==0||j==0)
        std::cout<<"error"<<std::endl;
        //return false;


    AdjListArcNode* p=new AdjListArcNode(j,NULL,_weight);
    p->nextArc=vexTable[i].firstArc;
    vexTable[i].firstArc=p;
    //无向图、另一条弧自行添加

    arcNum++;

    return true;
}

//--------------------删除弧--------------------/

template <typename T>
bool AdjListUndirGraph<T>::DeleteArc(T _name1,T _name2,float _weight)
{
    int i=LocateVex(_name1);
    int j=LocateVex(_name2);
    //如果不存在这两个节点、返回错误
    if(i=0||j=0)
        return false;
    AdjListArcNode* p;
    p->nextArc=vexTable[i].firstArc;
    //在位置i的边表中查找j
    while(p->nextArc!=nullptr&&p->nextArc->adjVex!=j)
        p=p->nextArc;
    if(p->nextArc->weight=_weight)
    {
        p->nextArc=p->nextArc->nextArc;
        delete p->nextArc;
        arcNum--;
    }
    //在位置j的边表中查找i、删除对称边
    p->nextArc=vexTable[j].firstArc;
    while(p->nextArc!=nullptr&&p->nextArc->adjVex!=i)
        p=p->nextArc;
    if(p->nextArc->weight=_weight)
    {
        p->nextArc=p->nextArc->nextArc;
        delete p->nextArc;
    }
    return ture;
}

//------------------深度优先遍历_递归------------------/
template <typename T>
bool AdjListUndirGraph<T>::DFS(int v)
{
    if(flag[v]!=1)
    {
        std::cout<<vexTable[v].name<<std::endl;
        flag[v]=1;
        AdjListArcNode* node=vexTable[v].firstArc;
        for(;node!=nullptr;node=node->nextArc)
            AdjListUndirGraph<T>::DFS(node->adjVex);
    }
    return true;
}

template <typename T>
bool AdjListUndirGraph<T>::DFSTraverse()
{
    for(int i=1;i<=vexNum;i++)
        flag[i]=0;

    for(int i=1;i<=vexNum;i++)
        if(flag[i]==0)
        {
            DFS(i);
        }
    return true;
}

//------------------广度优先遍历---------------------/

template <typename T>
bool AdjListUndirGraph<T>::BFS(int v)
{
    LinkQueue<int> queue;
    //进队列、标志位设为1
    queue.push(v);
    flag[v]=1;
    //输出节点元素
    std::cout<<vexTable[v].name<<std::endl;
    int i;
    AdjListArcNode* p;
    //队列非空
    while(!queue.isEmpty())
    {
        //获取队列头、出队列
        i=queue.getFront();
        queue.pop();
        for(p=vexTable[i].firstArc;p!=NULL;p=p->nextArc)
        {
            if(flag[p->adjVex]==0)
            {
                flag[p->adjVex]=1;
                std::cout<<"->"<<vexTable[p->adjVex].name<<std::endl;
                queue.push(p->adjVex);
            }

        }
    }

    return true;
}

template <typename T>
bool AdjListUndirGraph<T>::BFSTraverse()
{
    for(int i=1;i<=vexNum;i++)
        flag[i]=0;

    //若图是非连通图、以下for循环保证每个点都被遍历到
    for(int i=1;i<=vexNum;i++)
    {
        if(flag[i]==0)
        {
            BFS(i);
            //std::cout<<vexTable[i].name<<std::endl;
        }
    }
    return true;
}


#endif // GRAPH_H
