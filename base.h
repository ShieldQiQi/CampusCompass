/*
 * Date:2018-07-05
 * Author:SHIELD_QI
 * Project:CampusCompass
 * *************************************************/

//继承类模板的类的函数定义也要放在头文件内

#ifndef BASE_H
#define BASE_H

#include <QFile>
#include <QTextStream>
#include "graph.h"
#include "doublelink_list.h"
#include <QDebug>
using namespace std;

class DataInit:public AdjListUndirGraph<string>
{

public:
    DataInit();
    ~DataInit();

    QFile* qFile;
    QTextStream* qTextstream;

    //最短路径的双向链表存储
    DoubleLink<int> routine[36*36];

    int count=0;
    vector<vector<float>> coordinate;   //坐标二维数组
    vector<vector<float>> weight;       //权重数组
    vector<vector<int>> path;           //经过的顶点

    //弗洛伊德算法求最短路径
    bool DoFloyd(void);

    //将最短路径存入链表
    void RoutineCreate(int _num, int m , int n);

};

//------------------------------------函数成员定义-----------------------------------/

//构造函数、从文件中读取数据、存入邻接表
DataInit::DataInit()
{
    AdjListUndirGraph();

    //---------------读取地点名-----------------/
    qFile=new QFile("./data/name_cn1.txt");
    if (!qFile->open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    qTextstream=new QTextStream(qFile);
    while (!qTextstream->atEnd())
    {
        QString line = qTextstream->readLine();
        string str = string((const char *)line.toLocal8Bit());
        //插入顶点
        this->InsertVex(str);
    }

    //初始化各数组大小
    path.resize(vexNum+1,vector<int>(vexNum+1));
    weight.resize(vexNum+1,vector<float>(vexNum+1));
    coordinate.resize(vexNum+1,vector<float>(2));

    //---------------读取路径权重-----------------/
    qFile=new QFile("./data/weight1.txt");
    qFile->open(QIODevice::ReadOnly | QIODevice::Text);
    qTextstream=new QTextStream(qFile);
    //读取路径权值
    for (int i=1; i<=vexNum; i++)
        for (int j=i; j<=vexNum; j++)
        {
            QString line = qTextstream->readLine();
            weight[i][j]= line.toFloat();
            path[i][j]=j;
        }
    for(int i=1;i<=vexNum;i++)
        for (int j=1; j<i; j++)
        {
            weight[i][j]=weight[j][i];
            path[i][j]=j;
        }

    //------------------插入弧-------------------/
    for(int i=vexNum;i>0;i--)
    {
        for(int j=vexNum;j>0;j--)
        {
            this->InsertArc(vexTable[i].name,vexTable[j].name,weight[i][j]);
        }
    }
    //---------------读取坐标-----------------/
    qFile=new QFile("./data/coordinate1.txt");
    if (!qFile->open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    qTextstream=new QTextStream(qFile);
    for (int i=0; i<vexNum; i++)
        for (int j=0; j<2; j++)
        {
            QString line = qTextstream->readLine();
            coordinate[i][j]= line.toFloat();
        }

}

//弗洛伊德算法求最小权重
bool DataInit::DoFloyd(void)
{
    int i,j,k;                                                      //表示顶点i，j经过点k

    //---------------更新最小权重-----------------/
    for (k=1; k<=vexNum; k++)
    {
        for (i=1; i<=vexNum; i++)
            for (j=1; j<=vexNum; j++)
                if (weight[i][j]>weight[i][k]+weight[k][j])
                {
                    weight[i][j]=weight[i][k]+weight[k][j];
                    path[i][j]=k;
                }
    }

    //---------------生成最短路径-----------------/
    int num=0;
    for(int i=1;i<=vexNum;i++)
    {
        for(int j=1;j<=vexNum;j++)
        {
            //第num条路径【作为链表类对象】插入第一个节点、节点为第i个地址
            routine[num].insert(0,i);
            count++;
            //递归添加节点
            RoutineCreate(num,i,j);
            num++;
            count=0;
        }
    }
    return true;

}

//生成最短路径
void DataInit::RoutineCreate(int _num, int m, int n)
{
//    if(_num==1)
//      std::cout<<"routine[1].count"<<std::endl;
    if(path[m][n]==n)                            //如果经过的节点为j、表示路径只有一条边
    {
        routine[_num].insert(count,n);
        count++;

    }
    else                                         //否则：path[i][j]=k、判断 i，k 与 k j之间是否有其他点、如此循环
    {
//        std::cout<<" t ";
        RoutineCreate(_num,m,path[m][n]);
        RoutineCreate(_num,path[m][n],n);
    }
}

DataInit::~DataInit()
{
    delete qFile;
    delete qTextstream;
}


#endif // BASE_H
