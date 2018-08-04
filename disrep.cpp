#include "disrep.h"
//
#include <QDebug>

disrep::disrep(QObject *parent) :
    QObject(parent)
{
}

void disrep::notifyRegister()
{
    qDebug() << "register register register register register register register";
    qDebug() << "register register register register register register register";
    qDebug() << "register register register register register register register";
}

void disrep::notifyUnregister()
{
    qDebug() << "unregister unregister unregister unregister unregister unregister";
    qDebug() << "unregister unregister unregister unregister unregister unregister";
    qDebug() << "unregister unregister unregister unregister unregister unregister";
}

bool disrep::init(QStringList* p)
{
    if (p->size()<4)
        return false;

    // super_arm_helper_ = new SuperArmHelper(
                // p->at(0),
                // p->at(1),
                // p->at(2),
                // p->at(3));

    qDebug() << "complex: "+p->at(0);
    qDebug() << "name: "+p->at(1);
    qDebug() << "instance: "+p->at(2);
    qDebug() << "profile: "+p->at(3);

    //connect(super_arm_helper_, SIGNAL(disconnected()),this, SLOT(notifyUnregister()));
    //connect(super_arm_helper_, SIGNAL(connected()), this, SLOT(notifyRegister()));
    //connect(super_arm_helper_, SIGNAL(disrepair(QString,bool)), this, SLOT(notifyDisrepair(QString,bool)));

    this->keys = new QStringList();

    //    this->super_arm_helper_->logNotice(
    //                p->at(1)+" ПРОИНИЦИАЛИЗОРОВАН"
    //                );

    // return
            // super_arm_helper_->isConnected();
};

void disrep::notifyDisrepair(QString key, bool flag)
{
    qDebug() << "disrep::notifyDisrepair("+QString(key)+","+QString::number(flag)+")";
    //
    int i = this->keys->indexOf(key);
    switch(i)
    {
    case -1:
        if (!flag) return;
        this->keys->append(key);
        qDebug() << "this->keys->append("+key+")";
        break;
    default:
        if (flag) return;
        this->keys->removeAt(i);
        qDebug() << "this->keys->removeAt("+QString::number(i)+")";
        break;
    }
};

void disrep::repair(int i)
{
    qDebug() << "disrep::repair("+QString::number(i)+")";
    //
    qDebug() << "super_arm_helper_->setDisrepaired("+this->keys->at(i)+",true)";
    // super_arm_helper_->setDisrepaired(
                // this->keys->at(i),
                // true
                // );
    
    this->keys->removeAt(i);
    qDebug() << "this->keys->removeAt("+QString::number(i)+")";
    //
};
