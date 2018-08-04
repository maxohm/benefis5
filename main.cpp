#include "mainwindow.h"
//
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *rus = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForLocale(rus);

    QTranslator qtTranslator;
    qtTranslator.load("qtbase_ru");
    a.installTranslator(&qtTranslator);

    //    QString complex_id(argv[1]);
    //    QString instance(argv[2]);
    //    QString profile_id;

    //    if(argc > 3 && (QString("-noprofile")!=argv[3])) {
    //        profile_id = argv[3];  //проверяем наличие профиля
    //    };

    //    if(argc > 2){
    MainWindow w;
    w.dis = new disrep();
    if (w.dis->init(new QStringList(
                        QString(
                            "test;1394;1;profile"
                            ).split(";")
                        )
                    ))
        qDebug() << "We are almost there ...";
    //  };

    w.showMaximized();
    return a.exec();
}
