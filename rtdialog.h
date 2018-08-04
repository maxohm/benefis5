#ifndef RTDIALOG_H
#define RTDIALOG_H

#include <QDialog>

namespace Ui {
    class rtDialog;
}

class rtDialog : public QDialog
{
    Q_OBJECT

public:
    explicit rtDialog(QWidget *parent = 0);
    ~rtDialog();
    void setField(int i,QString v);
    QString getField(int i);

private:
    Ui::rtDialog *ui;
};

#endif // RTDIALOG_H
