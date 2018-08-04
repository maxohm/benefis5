#ifndef CHDIALOG_H
#define CHDIALOG_H

#include <QDialog>

namespace Ui {
    class chDialog;
}

class chDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chDialog(QWidget *parent = 0);
    ~chDialog();
    void setField(int i,QString v);
    QString getField(int i);

private:
    Ui::chDialog *ui;
};

#endif // CHDIALOG_H
