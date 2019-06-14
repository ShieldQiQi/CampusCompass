/*
 * Date:2018-07-03
 * Author:SHIELD_QI
 * Project:CampusCompass
 * *************************************************/

#include "dialog.h"
#include "drawer.h"
#include <QGridLayout>
#include <QToolBar>
#include <QApplication>
#include <QPushButton>
#include <QSplitter>
#include <QMovie>
#include <QLabel>
#include <QProgressDialog>
#include <QThread>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{

    QProgressDialog *progressDlg=new QProgressDialog(this);
    progressDlg->setWindowModality(Qt::WindowModal);
    progressDlg->setMinimumDuration(0);
    progressDlg->setAttribute(Qt::WA_DeleteOnClose, true);
    progressDlg->setWindowTitle(QStringLiteral("数据加载"));
    progressDlg->setLabelText(QStringLiteral("正在加载......"));
    progressDlg->setRange(0,800);
    progressDlg->setFixedSize(1100,880);
    progressDlg->setStyleSheet("QProgressBar{border:1px solid #FFFFFF;"
                              "height:50;"
                              "background:red;"
                              "text-align:center;"
                              "color:rgb(0,0,0);"
                              "border-radius:10px;}"
                              "QProgressBar::chunk{"
                              "border-radius:3px;"    // 斑马线圆角
                              "border:4px "
                              "solid green;" // 黑边，默认无边
                              "background-color:blue;}");
    progressDlg->show();
    progressDlg->move(603,20);
    QThread time;
    for(int i=1;i<800;i++)      //从1开始的
    {
         time.usleep (1);
         progressDlg->setValue(i);
         if(progressDlg->wasCanceled())
         {
         }
    }
    progressDlg->close();

    //控件_选择起始地和目的地
    Drawer* drawer=new Drawer;                            //创建Drawer类对象
    drawer->setWindowTitle("CampusCompass");
    drawer->setWindowIcon(QIcon("./image/index.ico"));
    drawer->setFixedSize(400,550);                        //设置窗口大小

    //绘图区域
    Paint* drawer2=new Paint();
    drawer2->setFixedSize(650,810);

    //工具栏
    ToolBar *toolbar=new ToolBar;
    toolbar->setFixedSize(650,30);
    toolbar->setStyleSheet("background-color: rgb(170, 0, 255);");
    QMainWindow* widget=new QMainWindow;
    widget->addToolBar(toolbar);

    //添加视频、音频
    player=new QMediaPlayer;
    player1=new QMediaPlayer;
    playerlist=new QMediaPlaylist;

    videoWidget = new QVideoWidget;
    player1->setVideoOutput(videoWidget);
    player1->setMedia(QUrl::fromLocalFile("./video/HITwh.mp4"));
    videoWidget->show();
    videoWidget->setFixedSize(400,250);
    player1->play();

    QPushButton *button=new QPushButton;
    button->setText(QStringLiteral("开启特效"));
    button->setFixedSize(401,30);
    button->setStyleSheet("background-color: rgb(170, 0, 255);");
    QObject::connect( button, SIGNAL(clicked(bool)), this,SLOT(popWidget(void)) );

    //左侧栏添加gif
    QMovie *movie_gif=new QMovie;
    movie_gif->setSpeed(100);
    movie_gif->setFileName("./image/gif.gif");
    QLabel* lable=new QLabel;
    lable->setFixedSize(100,850);
    lable->setMovie(movie_gif);
    movie_gif->start();

    //设置布局
    QGridLayout* mainLayout=new QGridLayout(this);       //用于布局管理器、将所有控件的位置固定
    mainLayout->addWidget((QWidget*)drawer,0,2);
    mainLayout->addWidget((QWidget*)drawer2,0,1);
    mainLayout->addWidget((QWidget*)widget,4,1);
    mainLayout->addWidget((QWidget*)videoWidget,3,2);
    mainLayout->addWidget((QWidget*)button,4,2);
//    mainLayout->addWidget((QWidget*)lable,0,0);
//    mainLayout->setAlignment((QWidget*)lable,Qt::AlignLeft);
    mainLayout->setAlignment((QWidget*)button,Qt::AlignLeft);
    mainLayout->setAlignment((QWidget*)drawer2,Qt::AlignLeft);
    mainLayout->setAlignment((QWidget*)widget,Qt::AlignLeft);
    mainLayout->setAlignment((QWidget*)videoWidget,Qt::AlignLeft);
    mainLayout->setAlignment((QWidget*)button,Qt::AlignLeft);
    setLayout((mainLayout));

    //播放音乐的信号和槽
    QObject::connect( toolbar, SIGNAL(itemClicked(int)), SLOT(Update(int)) );
    //绘图的信号和槽
    QObject::connect( drawer, SIGNAL(setRoutine(int,int)), drawer2,SLOT(paint(int,int)) );


    //设置背景图片
    this->setObjectName("dialog");    //这句话一定要有，不然，整个界面上的控件背景都跟界面背景一样
    this->setStyleSheet("QDialog#dialog{border-image:url(./image/background2.jpg)}");
}

Dialog::~Dialog()
{
    delete player;
    delete player1;
    delete playerlist;
    delete videoWidget;
}

void Dialog::Update(int theme)
{
    switch(theme)
    {
    case 1:
        this->setObjectName("dialog");
        this->setStyleSheet("QDialog#dialog{border-image:url(./image/left.jpg)}");
        break;
    case 2:
        this->setObjectName("dialog");
        this->setStyleSheet("QDialog#dialog{border-image:url(./image/background5.jpg)}");
        break;
    case 3:
        this->setObjectName("dialog");
        this->setStyleSheet("QDialog#dialog{border-image:url(./image/background6.jpg)}");
        break;
    case 4:
        this->setObjectName("dialog");
        this->setStyleSheet("QDialog#dialog{border-image:url(./image/background4.jpg)}");
        break;
    case 5:
        if(temp)
        {
            //设置播放列表、循环模式
            playerlist->addMedia(QMediaContent(QUrl("./music/langrenpipa.mp3")));
            playerlist->addMedia(QMediaContent(QUrl("./music/hello_summer.mp3")));
            playerlist->addMedia(QMediaContent(QUrl("./music/King.mp3")));

            playerlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            player->setVolume(50);
            player->setPlaylist(playerlist);
            player->play();
            player1->stop();
            temp=0;
        }else
        {
            player->stop();
            player1->play();
            temp=1;
        }
        break;
    }

}
