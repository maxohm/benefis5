#ifndef DISREP_H
#define DISREP_H
//
//include <superarmhelper.h>
#include <QApplication>

class disrep : public QObject
{
    Q_OBJECT

public:
    explicit disrep(QObject *parent = 0);
    bool init(QStringList* p);

private:
    void repair(int i);
//    SuperArmHelper* super_arm_helper_;
    QStringList* keys;

private slots:
    void notifyDisrepair(QString key, bool flag);
    void notifyRegister();
    void notifyUnregister();
};

#endif // DISREP_H
