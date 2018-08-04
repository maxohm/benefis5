#include "rtdialog.h"
#include "ui_rtdialog.h"


rtDialog::rtDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rtDialog)
{
    ui->setupUi(this);
}

rtDialog::~rtDialog()
{
    delete ui;
}

QString rtDialog::getField(int i)
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
        return ui->f2->currentText();
        break;
    case 3:
        return ui->f3->text();
        break;
    case 4:
        return ui->f4->currentText();
        break;
    case 5:
        return ui->f5->text();
        break;
    default:
        return "";
        break;
    }
}

void rtDialog::setField(int i,QString v)
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
        ui->f2->setCurrentIndex(ui->f2->findText(v));
        break;
    case 3:
        ui->f3->setText(v);
        break;
    case 4:
        ui->f4->setCurrentIndex(ui->f4->findText(v));
        break;
    case 5:
        ui->f5->setText(v);
        break;
    default:
        break;
    }
    qDebug("value set");
}
