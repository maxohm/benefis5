#ifndef RADIALOG_H
#define RADIALOG_H

#include <QDialog>

namespace Ui {
    class raDialog;
}

class raDialog : public QDialog
{
    Q_OBJECT

public:
    explicit raDialog(QWidget *parent = 0);
    ~raDialog();
    void setField(int i,QString v);
    QString getField(int i);

private:
    Ui::raDialog *ui;
};

#endif // RADIALOG_H
