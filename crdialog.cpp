#include "crdialog.h"
#include "ui_crdialog.h"

crDialog::crDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crDialog)
{
    ui->setupUi(this);
}

crDialog::~crDialog()
{
    delete ui;
}

QString crDialog::getField(int i)
{
    switch(i)
    {
    case 0:
        return ui->f0->text();
        break;
    case 1:
        return ui->f1->currentText();
        break;
    case 2:
        return ui->f2->currentText();
        break;
    case 3:
        return ui->f3->currentText();
        break;
    case 4:
        return ui->f4->text();
        break;
    case 5:
        return ui->f5->currentText();
        break;
    case 6:
        return ui->f6->text();
        break;
    default:
        return "";
        break;
    }
}

void crDialog::setField(int i,QString v)
{
    switch(i)
    {
    case 0:
        ui->f0->setText(v);
        break;
    case 1:
        ui->f1->setCurrentIndex(ui->f1->findText(v));
        break;
    case 2:
        ui->f2->setCurrentIndex(ui->f2->findText(v));
        break;
    case 3:
        ui->f3->setCurrentIndex(ui->f3->findText(v));
        break;
    case 4:
        ui->f4->setText(v);
        break;
    case 5:
        ui->f5->setCurrentIndex(ui->f5->findText(v));
        break;
    case 6:
        ui->f6->setText(v);
        break;
    default:
        break;
    }
}
