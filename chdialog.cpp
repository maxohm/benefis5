#include "chdialog.h"
#include "ui_chdialog.h"

chDialog::chDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chDialog)
{
    ui->setupUi(this);
}

chDialog::~chDialog()
{
    delete ui;
}

QString chDialog::getField(int i)
{
/*
    QWidget *tmp;
    QString cname;

    tmp = this->findChild<QWidget *>("f"+QString::number(i));
    cname = QString(tmp->metaObject()->className());

    if(cname=="QComboBox") return QComboBox(tmp).currentText();
    if(cname=="QLineEdit") return QLineEdit(tmp).text();
    return "";
*/
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
    case 3:
        return ui->f3->currentText();
        break;
    case 4:
        return ui->f4->currentText();
        break;
    case 5:
        return ui->f5->currentText();
        break;
    case 6:
        return ui->f6->currentText();
        break;
    case 7:
        return ui->f7->currentText();
        break;
    case 8:
        return ui->f8->currentText();
        break;
    case 9:
        return ui->f9->currentText();
        break;
    case 10:
        return ui->f10->currentText();
        break;
    case 11:
        if (ui->f11->isChecked()) return "+";
        return "-";
        break;
    default:
        return "";
        break;
    }
}

void chDialog::setField(int i,QString v)
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
    case 3:
        ui->f3->setCurrentIndex(ui->f3->findText(v));
        break;
    case 4:
        ui->f4->setCurrentIndex(ui->f4->findText(v));
        break;
    case 5:
        ui->f5->setCurrentIndex(ui->f5->findText(v));
        break;
    case 6:
        ui->f6->setCurrentIndex(ui->f6->findText(v));
        break;
    case 7:
        ui->f7->setCurrentIndex(ui->f7->findText(v));
        break;
    case 8:
        ui->f8->setCurrentIndex(ui->f8->findText(v));
        break;
    case 9:
        ui->f9->setCurrentIndex(ui->f9->findText(v));
        break;
    case 10:
        ui->f10->setCurrentIndex(ui->f10->findText(v));
        break;
    case 11:
        if (v=="+") ui->f11->setChecked(true);
        break;
    default:
        break;
    }
}
