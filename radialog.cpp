#include "radialog.h"
#include "ui_radialog.h"

raDialog::raDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::raDialog)
{
    ui->setupUi(this);
}

raDialog::~raDialog()
{
    delete ui;
}

QString raDialog::getField(int i)
{
    switch(i)
    {
    case 0:
        return ui->f0->text();
        break;
    case 1:
        return ui->f1->text();
        break;
    case 2:
        return ui->f2->text();
        break;
    default:
        return "";
        break;
    }
}

void raDialog::setField(int i,QString v)
{
    switch(i)
    {
    case 0:
        ui->f0->setText(v);
        break;
    case 1:
        ui->f1->setText(v);
        break;
    case 2:
        ui->f2->setText(v);
        break;
    default:
        break;
    }
}
