#include "mainwindow.h"
//
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QTranslator qtTranslator;

#ifndef HAVE_QT5
    QTextCodec *rus = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(rus);   
	qtTranslator.load("qt_ru","");
#else
    QTextCodec *rus = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForLocale(rus);
	qtTranslator.load("qtbase_ru");
#endif

    a.installTranslator(&qtTranslator);

    //    QString complex_id(argv[1]);
    //    QString instance(argv[2]);
    //    QString profile_id;

    //    if(argc > 3 && (QString("-noprofile")!=argv[3])) {
    //        profile_id = argv[3];  //проверяем наличие профиля
    //    };

    //    if(argc > 2){
    MainWindow w;
    //w.dis = new disrep();
    //if (w.dis->init(new QStringList(
    //                    QString(
    //                        "test;1394;1;profile"
    //                        ).split(";")
    //                    )
    //                ))
    //    qDebug() << "We are almost there ...";
    //  };

    w.showMaximized();
    return a.exec();
}
