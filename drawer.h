/*
 * Date:2018-07-03
 * Author:SHIELD_QI
 * Project:CampusCompass
 * *************************************************/

#ifndef DRAWER_H
#define DRAWER_H

#include <QToolBox>
#include <QToolButton>
#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QToolBar>
#include "doublelink_list.h"

using namespace std;

//Drawer 类继承自QToolBox类、用于选择目的地和出发地
class Drawer : public QToolBox
{
    Q_OBJECT
public:
    Drawer(QWidget* parent=0,Qt::WindowFlags f=0);
    ~Drawer()
    {

        for(int i=0;i<36;i++)
            delete tool_Btn1[i];
        for(int i=0;i<36;i++)
            delete tool_Btn2[i];

    }
    int var_0=0;
    int var_1=0;

private:
    QToolButton *tool_Btn1[36];
    QToolButton *tool_Btn2[36];
    QToolButton *url_Btn[10];
signals:
    void setRoutine(int identifier1,int identifier2);
public slots:
    void emitSignal1_1(void);
    void emitSignal1_2(void);
    void emitSignal1_3(void);
    void emitSignal1_4(void);
    void emitSignal1_5(void);
    void emitSignal1_6(void);
    void emitSignal1_7(void);
    void emitSignal1_8(void);
    void emitSignal1_9(void);
    void emitSignal1_10(void);
    void emitSignal1_11(void);
    void emitSignal1_12(void);
    void emitSignal1_13(void);
    void emitSignal1_14(void);
    void emitSignal1_15(void);
    void emitSignal1_16(void);
    void emitSignal1_17(void);
    void emitSignal1_18(void);
    void emitSignal1_19(void);
    void emitSignal1_20(void);
    void emitSignal1_21(void);
    void emitSignal1_22(void);
    void emitSignal1_23(void);
    void emitSignal1_24(void);
    void emitSignal1_25(void);
    void emitSignal1_26(void);
    void emitSignal1_27(void);
    void emitSignal1_28(void);
    void emitSignal1_29(void);
    void emitSignal1_30(void);
    void emitSignal1_31(void);
    void emitSignal1_32(void);
    void emitSignal1_33(void);
    void emitSignal1_34(void);
    void emitSignal1_35(void);
    void emitSignal1_36(void);

    void emitSignal2_1(void);
    void emitSignal2_2(void);
    void emitSignal2_3(void);
    void emitSignal2_4(void);
    void emitSignal2_5(void);
    void emitSignal2_6(void);
    void emitSignal2_7(void);
    void emitSignal2_8(void);
    void emitSignal2_9(void);
    void emitSignal2_10(void);
    void emitSignal2_11(void);
    void emitSignal2_12(void);
    void emitSignal2_13(void);
    void emitSignal2_14(void);
    void emitSignal2_15(void);
    void emitSignal2_16(void);
    void emitSignal2_17(void);
    void emitSignal2_18(void);
    void emitSignal2_19(void);
    void emitSignal2_20(void);
    void emitSignal2_21(void);
    void emitSignal2_22(void);
    void emitSignal2_23(void);
    void emitSignal2_24(void);
    void emitSignal2_25(void);
    void emitSignal2_26(void);
    void emitSignal2_27(void);
    void emitSignal2_28(void);
    void emitSignal2_29(void);
    void emitSignal2_30(void);
    void emitSignal2_31(void);
    void emitSignal2_32(void);
    void emitSignal2_33(void);
    void emitSignal2_34(void);
    void emitSignal2_35(void);
    void emitSignal2_36(void);

    void on_clicked_1(void);
    void on_clicked_2(void);
    void on_clicked_3(void);
    void on_clicked_4(void);
    void on_clicked_5(void);
    void on_clicked_6(void);
    void on_clicked_7(void);
    void on_clicked_8(void);
    void on_clicked_9(void);
    void on_clicked_10(void);
};

//Paint 类继承自QWidget类、用于画图区
class Paint:public QWidget
{
    Q_OBJECT

public:

    int point1=0,point2=0;

    vector<vector<float>> coordinate_paint;   //坐标二维数组

    Paint()
    {
    }
    ~Paint(){}
private:
    DoubleLink<int> Routine[15];              //路径数组
protected:
    void paintEvent(QPaintEvent *);

public slots:
    void paint(int identifier1,int identifier2);
};

//ToolBar 类继承自QMainWindow类、用作菜单栏
class ToolBar : public QToolBar
{
    Q_OBJECT

public:
    ToolBar(QWidget *parent = 0);
    ~ToolBar();

    int Flag=1;
    QMenuBar*         m_pMenuBar;
    QAction*          m_arrAct[6];
    QMenu*            m_pMenu;
    QMenu*            m_pMenu1;
public slots:
    void OnClick1(void);
    void OnClick2(void);
    void OnClick3(void);
    void OnClick4(void);
    void OnClick5(void);
    void OnClick6(void);
protected:
    void  resizeEvent(QResizeEvent *e);
signals:
    void itemClicked(int theme);
};


#endif // DRAWER_H
