/*
 * Auhtor:SHIELD_QI
 * Date:2018-07-03
 * Project:CampusCompass
 * *****************************************************/

#include "dialog.h"
#include <QApplication>
#include "drawer.h"
#include "graph.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog w;

    w.setWindowTitle("SHIELD_QI");
    w.setFixedSize(1100,880);
    w.setWindowIcon((QIcon)"./image/index.ico");
    w.setStyleSheet("background-color: rgb(255,255,255)");
    w.move(603,20);
    w.setStyleSheet("QDialog#dialog{border-image:url(./image/hrt.ico)}");
    w.show();

    return a.exec();
}
