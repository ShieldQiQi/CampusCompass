/*
 * Date:2018-07-03
 * Author:SHIELD_QI
 * Project:CampusCompass
 * *************************************************/

#ifndef DIALOG_H
#define DIALOG_H

#include <QPushButton>
#include <QDialog>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimedia/QMediaControl>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QGridLayout>

//播放音乐要添加依赖库
#pragma comment(lib,"Qt5Multimedia.lib")
#pragma comment(lib,"Qt5MultimediaWIdgets.lib")

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    int temp=1;
    QMediaPlaylist* playerlist;
    QMediaPlayer* player;
    QMediaPlayer* player1;
    QVideoWidget *videoWidget;
public slots:
    void Update(int theme);
    void popWidget(void)
    {
        QDialog *dialog_pop=new QDialog;
        dialog_pop->setFixedSize(500,100);
        QPushButton *button_pop=new QPushButton;
        button_pop->setFixedSize(350,30);
        button_pop->setText(QStringLiteral("特效是不可能有的，这辈子都不可能有！"));
        QGridLayout* mainLayout=new QGridLayout(this);       //用于布局管理器、将所有控件的位置固定
        mainLayout->addWidget((QWidget*)button_pop,0,0);
        dialog_pop->setLayout((mainLayout));
        dialog_pop->setWindowTitle("Free All the motor function");
        dialog_pop->show();
    }
};

#endif // DIALOG_H
