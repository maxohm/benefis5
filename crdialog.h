#ifndef CRDIALOG_H
#define CRDIALOG_H

#include <QDialog>

namespace Ui {
    class crDialog;
}

class crDialog : public QDialog
{
    Q_OBJECT

public:
    explicit crDialog(QWidget *parent = 0);
    ~crDialog();
    void setField(int i,QString v);
    QString getField(int i);

private:
    Ui::crDialog *ui;
};

#endif // CRDIALOG_H
