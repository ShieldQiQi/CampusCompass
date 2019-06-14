/*
 * Date:2018-07-03
 * Author:SHIELD_QI
 * Project:CampusCompass
 * *************************************************/

#include "drawer.h"
#include "base.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGraphicsColorizeEffect>
#include <QIcon>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QImage>
#include "dialog.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "doublelink_list.h"
#include <QDesktopServices>

//------------------------------------------------------------侧栏函数定义
Drawer::Drawer(QWidget* parent,Qt::WindowFlags f)
    :QToolBox(parent,f)
{

    QFile* qFile1,* qFile2;
    QTextStream* qTextstream1,*qTextstream2;
    qFile1=new QFile("./data/name_cn1.txt");
    if (!qFile1->open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    qTextstream1=new QTextStream(qFile1);
    //--------------------------------------------布局一------------------------------------------/
    for(int i=0;i<36;i++)
    {
        QString line = qTextstream1->readLine();
        tool_Btn1[i]=new QToolButton(this);
        tool_Btn1[i]->setText(line);
        tool_Btn1[i]->setIcon(QIcon("./image/mushrooms.png"));
        tool_Btn1[i]->setIconSize(QSize(40,40));
        tool_Btn1[i]->setAutoRaise(true);
        tool_Btn1[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    }

    QGroupBox *groupBox1=new QGroupBox;                 //对应每一个抽屉
    //设置模糊度
    QGraphicsBlurEffect *g1 = new QGraphicsBlurEffect(this);
    g1->setBlurRadius(1.5);
    groupBox1->setGraphicsEffect(g1);

    //设置抽屉内每个按钮的布局
    QVBoxLayout *layout1=new QVBoxLayout(groupBox1);
    layout1->setMargin(10);                             //布局中个窗体的显示间距
    layout1->setAlignment(Qt::AlignLeft);               //左对齐
    //在布局中添加组件_在抽屉中添加按钮
    for(int i=0;i<36;i++)
        layout1->addWidget(tool_Btn1[i]);

    layout1->addStretch();                              //插入一个占位符、使所有按钮能够向上对齐

    //--------------------------------------------布局二------------------------------------------/
    qFile2=new QFile("./data/name_cn1.txt");
    if (!qFile2->open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    qTextstream2=new QTextStream(qFile2);
    for(int i=0;i<36;i++)
    {
        QString line = qTextstream2->readLine();
        tool_Btn2[i]=new QToolButton(this);
        tool_Btn2[i]->setText(line);
        tool_Btn2[i]->setIcon(QIcon("./image/download.jpg"));
        tool_Btn2[i]->setIconSize(QSize(40,40));
        tool_Btn2[i]->setAutoRaise(true);
        tool_Btn2[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    }

    QGroupBox *groupBox2=new QGroupBox;
    //设置图形效果
    QGraphicsBlurEffect *g2 = new QGraphicsBlurEffect(this);
    g2->setBlurRadius(1.5);
    groupBox2->setGraphicsEffect(g2);

    QVBoxLayout *layout2=new QVBoxLayout(groupBox2);

    layout2->setMargin(10);                   //布局中个窗体的显示间距
    layout2->setAlignment(Qt::AlignLeft);     //中间对齐

    //在布局中添加组件
    for(int i=0;i<36;i++)
        layout2->addWidget(tool_Btn2[i]);
    layout2->addStretch();                              //插入一个占位符、使所有按钮能够向上对齐
    //--------------------------------------------布局三------------------------------------------/

    for(int i=0;i<10;i++)
    {
        url_Btn[i]=new QToolButton(this);
        url_Btn[i]->setIcon(QIcon("./image/index.png"));
        url_Btn[i]->setIconSize(QSize(40,40));
        url_Btn[i]->setAutoRaise(true);
        url_Btn[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    }
    url_Btn[0]->setText(QStringLiteral("哈工大威海校内信息网"));
    url_Btn[1]->setText(QStringLiteral("哈工大威海教务处"));
    url_Btn[2]->setText(QStringLiteral("观海听涛官网"));
    url_Btn[3]->setText(QStringLiteral("学生个人信息系统"));
    url_Btn[4]->setText(QStringLiteral("电子技术实验中心"));
    url_Btn[5]->setText(QStringLiteral("物理实验中心"));
    url_Btn[6]->setText(QStringLiteral("观海听涛百度贴吧"));
    url_Btn[7]->setText(QStringLiteral("哈工大威海数据结构"));
    url_Btn[8]->setText(QStringLiteral("哈工大威海知乎话题"));
    url_Btn[9]->setText(QStringLiteral("百川PT"));

    QGroupBox *groupBox3=new QGroupBox;
    QVBoxLayout *layout3=new QVBoxLayout(groupBox3);
    layout3->setMargin(10);                 //布局中个窗体的显示间距
    layout3->setAlignment(Qt::AlignLeft);   //中间对齐
    for(int i=0;i<10;i++)
        layout3->addWidget(url_Btn[i]);
    layout3->addStretch();                  //插入一个占位符、使所有按钮能够向上对齐
    //设置图形效果
    QGraphicsBlurEffect *g3 = new QGraphicsBlurEffect(this);
    g3->setBlurRadius(1.5);
    groupBox3->setGraphicsEffect(g3);

    //将准备好的抽屉插入ToolBox
    this->addItem((QWidget*)groupBox1,QStringLiteral("起始地"));
    this->addItem((QWidget*)groupBox2,QStringLiteral("目的地"));
    this->addItem((QWidget*)groupBox3,QStringLiteral("工大指南"));

    //我也不想这么做
    QObject::connect( tool_Btn1[0], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_1(void)) );
    QObject::connect( tool_Btn1[1], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_2(void)) );
    QObject::connect( tool_Btn1[2], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_3(void)) );
    QObject::connect( tool_Btn1[3], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_4(void)) );
    QObject::connect( tool_Btn1[4], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_5(void)) );
    QObject::connect( tool_Btn1[5], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_6(void)) );
    QObject::connect( tool_Btn1[6], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_7(void)) );
    QObject::connect( tool_Btn1[7], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_8(void)) );
    QObject::connect( tool_Btn1[8], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_9(void)) );
    QObject::connect( tool_Btn1[9], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_10(void)) );
    QObject::connect( tool_Btn1[10], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_11(void)) );
    QObject::connect( tool_Btn1[11], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_12(void)) );
    QObject::connect( tool_Btn1[12], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_13(void)) );
    QObject::connect( tool_Btn1[13], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_14(void)) );
    QObject::connect( tool_Btn1[14], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_15(void)) );
    QObject::connect( tool_Btn1[15], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_16(void)) );
    QObject::connect( tool_Btn1[16], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_17(void)) );
    QObject::connect( tool_Btn1[17], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_18(void)) );
    QObject::connect( tool_Btn1[18], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_19(void)) );
    QObject::connect( tool_Btn1[19], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_20(void)) );
    QObject::connect( tool_Btn1[20], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_21(void)) );
    QObject::connect( tool_Btn1[21], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_22(void)) );
    QObject::connect( tool_Btn1[22], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_23(void)) );
    QObject::connect( tool_Btn1[23], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_24(void)) );
    QObject::connect( tool_Btn1[24], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_25(void)) );
    QObject::connect( tool_Btn1[25], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_26(void)) );
    QObject::connect( tool_Btn1[26], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_27(void)) );
    QObject::connect( tool_Btn1[27], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_28(void)) );
    QObject::connect( tool_Btn1[28], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_29(void)) );
    QObject::connect( tool_Btn1[29], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_30(void)) );
    QObject::connect( tool_Btn1[30], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_31(void)) );
    QObject::connect( tool_Btn1[31], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_32(void)) );
    QObject::connect( tool_Btn1[32], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_33(void)) );
    QObject::connect( tool_Btn1[33], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_34(void)) );
    QObject::connect( tool_Btn1[34], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_35(void)) );
    QObject::connect( tool_Btn1[35], SIGNAL(clicked(bool)), this,SLOT(emitSignal1_36(void)) );

    QObject::connect( tool_Btn2[0], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_1(void)) );
    QObject::connect( tool_Btn2[1], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_2(void)) );
    QObject::connect( tool_Btn2[2], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_3(void)) );
    QObject::connect( tool_Btn2[3], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_4(void)) );
    QObject::connect( tool_Btn2[4], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_5(void)) );
    QObject::connect( tool_Btn2[5], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_6(void)) );
    QObject::connect( tool_Btn2[6], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_7(void)) );
    QObject::connect( tool_Btn2[7], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_8(void)) );
    QObject::connect( tool_Btn2[8], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_9(void)) );
    QObject::connect( tool_Btn2[9], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_10(void)) );
    QObject::connect( tool_Btn2[10], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_11(void)) );
    QObject::connect( tool_Btn2[11], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_12(void)) );
    QObject::connect( tool_Btn2[12], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_13(void)) );
    QObject::connect( tool_Btn2[13], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_14(void)) );
    QObject::connect( tool_Btn2[14], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_15(void)) );
    QObject::connect( tool_Btn2[15], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_16(void)) );
    QObject::connect( tool_Btn2[16], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_17(void)) );
    QObject::connect( tool_Btn2[17], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_18(void)) );
    QObject::connect( tool_Btn2[18], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_19(void)) );
    QObject::connect( tool_Btn2[19], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_20(void)) );
    QObject::connect( tool_Btn2[20], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_21(void)) );
    QObject::connect( tool_Btn2[21], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_22(void)) );
    QObject::connect( tool_Btn2[22], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_23(void)) );
    QObject::connect( tool_Btn2[23], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_24(void)) );
    QObject::connect( tool_Btn2[24], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_25(void)) );
    QObject::connect( tool_Btn2[25], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_26(void)) );
    QObject::connect( tool_Btn2[26], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_27(void)) );
    QObject::connect( tool_Btn2[27], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_28(void)) );
    QObject::connect( tool_Btn2[28], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_29(void)) );
    QObject::connect( tool_Btn2[29], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_30(void)) );
    QObject::connect( tool_Btn2[30], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_31(void)) );
    QObject::connect( tool_Btn2[31], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_32(void)) );
    QObject::connect( tool_Btn2[32], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_33(void)) );
    QObject::connect( tool_Btn2[33], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_34(void)) );
    QObject::connect( tool_Btn2[34], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_35(void)) );
    QObject::connect( tool_Btn2[35], SIGNAL(clicked(bool)), this,SLOT(emitSignal2_36(void)) );

    QObject::connect( url_Btn[0], SIGNAL(clicked(bool)), this,SLOT(on_clicked_1(void)) );
    QObject::connect( url_Btn[1], SIGNAL(clicked(bool)), this,SLOT(on_clicked_2(void)) );
    QObject::connect( url_Btn[2], SIGNAL(clicked(bool)), this,SLOT(on_clicked_3(void)) );
    QObject::connect( url_Btn[3], SIGNAL(clicked(bool)), this,SLOT(on_clicked_4(void)) );
    QObject::connect( url_Btn[4], SIGNAL(clicked(bool)), this,SLOT(on_clicked_5(void)) );
    QObject::connect( url_Btn[5], SIGNAL(clicked(bool)), this,SLOT(on_clicked_6(void)) );
    QObject::connect( url_Btn[6], SIGNAL(clicked(bool)), this,SLOT(on_clicked_7(void)) );
    QObject::connect( url_Btn[7], SIGNAL(clicked(bool)), this,SLOT(on_clicked_8(void)) );
    QObject::connect( url_Btn[8], SIGNAL(clicked(bool)), this,SLOT(on_clicked_9(void)) );
    QObject::connect( url_Btn[9], SIGNAL(clicked(bool)), this,SLOT(on_clicked_10(void)) );
}

void Drawer::on_clicked_1(void)
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://today.hitwh.edu.cn/index.asp")));
}
void Drawer::on_clicked_2(void)
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://jwc.hitwh.edu.cn")));
}
void Drawer::on_clicked_3(void)
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://blog.const.net.cn")));
}
void Drawer::on_clicked_4(void)
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://222.194.15.1:7777/zhxt_bks/zhxt_bks.html")));
}
void Drawer::on_clicked_5(void)
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://eelab.hitwh.edu.cn/")));
}
void Drawer::on_clicked_6(void)
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://jwc.hitwh.edu.cn")));
}
void Drawer::on_clicked_7(void)
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://tieba.baidu.com/f?kw=%B9%DB%BA%A3%CC%FD%CC%CE&fr=ala0&tpl=5")));
}
void Drawer::on_clicked_8(void)
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://ds.hitwh.edu.cn")));
}
void Drawer::on_clicked_9(void)
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://www.zhihu.com/topic/19736330/newest")));
}
void Drawer::on_clicked_10(void)
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://pt.ghtt.net/login.php")));
}

void Drawer::emitSignal1_1(void)
{
    var_0=1;
}
void Drawer::emitSignal1_2(void)
{
    var_0=2;
}
void Drawer::emitSignal1_3(void)
{
    var_0=3;
}
void Drawer::emitSignal1_4(void)
{

    var_0=4;
}
void Drawer::emitSignal1_5(void)
{

    var_0=5;
}
void Drawer::emitSignal1_6(void)
{

    var_0=6;
}
void Drawer::emitSignal1_7(void)
{

    var_0=7;
}
void Drawer::emitSignal1_8(void)
{

    var_0=8;
}
void Drawer::emitSignal1_9(void)
{

    var_0=9;
}
void Drawer::emitSignal1_10(void)
{

    var_0=10;
}
void Drawer::emitSignal1_11(void)
{

    var_0=11;
}
void Drawer::emitSignal1_12(void)
{

    var_0=12;
}
void Drawer::emitSignal1_13(void)
{

    var_0=13;
}
void Drawer::emitSignal1_14(void)
{

    var_0=14;
}
void Drawer::emitSignal1_15(void)
{

    var_0=15;
}
void Drawer::emitSignal1_16(void)
{

    var_0=16;
}
void Drawer::emitSignal1_17(void)
{

    var_0=17;
}
void Drawer::emitSignal1_18(void)
{

    var_0=18;
}
void Drawer::emitSignal1_19(void)
{

    var_0=19;
}
void Drawer::emitSignal1_20(void)
{

    var_0=20;
}
void Drawer::emitSignal1_21(void)
{

    var_0=21;
}
void Drawer::emitSignal1_22(void)
{

    var_0=22;
}
void Drawer::emitSignal1_23(void)
{

    var_0=23;
}
void Drawer::emitSignal1_24(void)
{

    var_0=24;
}
void Drawer::emitSignal1_25(void)
{

    var_0=25;
}
void Drawer::emitSignal1_26(void)
{

    var_0=26;
}
void Drawer::emitSignal1_27(void)
{

    var_0=27;
}
void Drawer::emitSignal1_28(void)
{

    var_0=28;
}
void Drawer::emitSignal1_29(void)
{

    var_0=29;
}
void Drawer::emitSignal1_30(void)
{

    var_0=30;
}
void Drawer::emitSignal1_31(void)
{

    var_0=31;
}
void Drawer::emitSignal1_32(void)
{

    var_0=32;
}
void Drawer::emitSignal1_33(void)
{

    var_0=33;
}
void Drawer::emitSignal1_34(void)
{

    var_0=34;
}
void Drawer::emitSignal1_35(void)
{

    var_0=35;
}
void Drawer::emitSignal1_36(void)
{

    var_0=36;
}

void Drawer::emitSignal2_1(void)
{
    var_1=1;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_2(void)
{

    var_1=2;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_3(void)
{

    var_1=3;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_4(void)
{

    var_1=4;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_5(void)
{

    var_1=5;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_6(void)
{

    var_1=6;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_7(void)
{

    var_1=7;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_8(void)
{

    var_1=8;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_9(void)
{

    var_1=9;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_10(void)
{

    var_1=10;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_11(void)
{

    var_1=11;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_12(void)
{

    var_1=12;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_13(void)
{

    var_1=13;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_14(void)
{

    var_1=14;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_15(void)
{

    var_1=15;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_16(void)
{

    var_1=16;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_17(void)
{

    var_1=17;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_18(void)
{

    var_1=18;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_19(void)
{

    var_1=19;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_20(void)
{

    var_1=20;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_21(void)
{

    var_1=21;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_22(void)
{

    var_1=22;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_23(void)
{

    var_1=23;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_24(void)
{

    var_1=24;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_25(void)
{

    var_1=25;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_26(void)
{

    var_1=26;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_27(void)
{

    var_1=27;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_28(void)
{

    var_1=28;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_29(void)
{

    var_1=29;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_30(void)
{

    var_1=30;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_31(void)
{
    var_1=31;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_32(void)
{

    var_1=32;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_33(void)
{

    var_1=33;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_34(void)
{

    var_1=34;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_35(void)
{

    var_1=35;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}
void Drawer::emitSignal2_36(void)
{

    var_1=36;
    emit setRoutine(var_0,var_1);
    var_0=0;
    var_1=0;
}

//------------------------------------------------------------绘图区函数定义
void Paint::paintEvent(QPaintEvent *)
{
    //加载数据
    DataInit data1;
    //弗洛伊德算法求最短路径
    data1.DoFloyd();

    QPainter painter(this);
    QPixmap pixmap("./image/Hit.jpg");
    QPen pen;
    pen.setWidth(6);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    //贴一张图片
    painter.drawPixmap(0,0,650,820,pixmap);
    //画一条直线
    pen.setColor(Qt::yellow);
    painter.setPen(pen);

    if(point1>0&&point2>0)
        for(Node<int>* temp=data1.routine[36*(point1-1)+point2-1].getHead();temp!=NULL;temp=temp->next)
        {
            //循环画出路径中每个顶点
            painter.drawEllipse(QPointF(data1.coordinate[temp->value-1][0],data1.coordinate[temp->value-1][1]),12,12);
            //将路径中每个顶点进行连接
            if(temp->next!=nullptr)
                painter.drawLine(QPointF(data1.coordinate[temp->value-1][0],data1.coordinate[temp->value-1][1]),QPointF(data1.coordinate[temp->next->value-1][0],data1.coordinate[temp->next->value-1][1]));
        }
}

void Paint::paint(int identifier1,int identifier2)
{
    point1=identifier1;
    point2=identifier2;

    QDialog *image_pop=new QDialog;
    image_pop->setFixedSize(500,300);
    image_pop->setObjectName("dialog");

    if(point2==3)
    {
        image_pop->setWindowTitle(QStringLiteral("主楼—图片"));
        image_pop->setStyleSheet("QDialog#dialog{border-image:url(./image/timg.jpg)}");
        image_pop->show();
        image_pop->move(100,20);
    }else if(point2==9)
    {
        image_pop->setWindowTitle(QStringLiteral("图书馆—图片"));
        image_pop->setStyleSheet("QDialog#dialog{border-image:url(./image/libirary.jpg)}");
        image_pop->show();
        image_pop->move(100,20);
    }

    this->update();
}


//------------------------------------------------------------菜单栏函数定义
ToolBar::ToolBar(QWidget *parent)
    : QToolBar(parent)
{
    m_pMenuBar = new QMenuBar(this);
    m_arrAct[0] = new QAction(QStringLiteral("来首音乐"), this);
    m_arrAct[1] = new QAction(QStringLiteral("退出"), this);
    m_arrAct[2] = new QAction(QStringLiteral("小清新"), this);
    m_arrAct[3] = new QAction(QStringLiteral("中情新"), this);
    m_arrAct[4] = new QAction(QStringLiteral("大清新"), this);
    m_arrAct[5] = new QAction(QStringLiteral("超级清新"), this);

    m_pMenu = new QMenu(QStringLiteral("更换主题"));
    m_pMenu1 = new QMenu(QStringLiteral("                              支付宝：17863110617"));

    m_pMenu->addAction(m_arrAct[2]);
    m_pMenu->addAction(m_arrAct[3]);
    m_pMenu->addAction(m_arrAct[4]);
    m_pMenu->addAction(m_arrAct[5]);

    m_pMenuBar->addAction(m_arrAct[0]);
    m_pMenuBar->addAction(m_arrAct[1]);
    m_pMenuBar->addMenu(m_pMenu);
    m_pMenuBar->addMenu(m_pMenu1);

    QObject::connect(m_arrAct[0], SIGNAL(triggered()),
            this, SLOT(OnClick1()));
    //退出界面
    QObject::connect( m_arrAct[1], SIGNAL(triggered()), qApp, SLOT(quit()) );
    //刷新界面颜色
    QObject::connect(m_arrAct[2], SIGNAL(triggered()),
            this, SLOT(OnClick3()));
//    QObject::connect( m_arrAct[2], SIGNAL(triggered()), qApp, SLOT(quit()) );
    QObject::connect(m_arrAct[3], SIGNAL(triggered()),
            this, SLOT(OnClick4()));
    QObject::connect(m_arrAct[4], SIGNAL(triggered()),
            this, SLOT(OnClick5()));
    QObject::connect(m_arrAct[5], SIGNAL(triggered()),
            this, SLOT(OnClick6()));
}

ToolBar::~ToolBar()
{
    delete m_pMenuBar;
    delete m_pMenu;
    delete m_pMenu1;
    delete m_arrAct[0];
    delete m_arrAct[1];
    delete m_arrAct[2];
    delete m_arrAct[3];
    delete m_arrAct[4];
    delete m_arrAct[5];
}

void ToolBar::resizeEvent(QResizeEvent *e)
{
    m_pMenuBar->setGeometry(0,0,width(), 50);
}

void ToolBar::OnClick1(void)
{
    if(Flag)
    {
        m_arrAct[0]->setText(QStringLiteral("关闭音乐"));
        Flag=0;
    }else
    {
        m_arrAct[0]->setText(QStringLiteral("播放音乐"));
        Flag=1;
    }
    emit itemClicked(5);
}
void ToolBar::OnClick2(void)
{
//    QApplication* app;
//    app->quit();
}
void ToolBar::OnClick3(void)
{
    //发射信号、基佬绿
    emit itemClicked(1);
}
void ToolBar::OnClick4(void)
{
    //发射信号、基佬蓝
    emit itemClicked(2);
}
void ToolBar::OnClick5(void)
{
    //发射信号、基佬红
    emit itemClicked(3);
}
void ToolBar::OnClick6(void)
{
    //发射信号、基佬黄
    emit itemClicked(4);
}
