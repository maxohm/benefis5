#include "mainwindow.h"
#include "ui_mainwindow.h"
//
#include <QDate>
#include <QTimer>
#include <QFile>
//#include <QTime>
#include <QXmlStreamReader>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer_reconnect = new QTimer(this);
    connect(timer_reconnect, SIGNAL(timeout()), this, SLOT(slotReconnect()));

    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_3,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_4,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->action_5,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_6,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_6,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_7,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_8,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_9,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_A,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_B,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_C,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_D,SIGNAL(triggered()),this,SLOT(tabdial()));
    connect(ui->action_E,SIGNAL(triggered()),this,SLOT(tabdial()));

    ui->rttab->horizontalHeader()->setVisible(true);
    ui->ratab->horizontalHeader()->setVisible(true);
    ui->chtab->horizontalHeader()->setVisible(true);
    ui->crtab->horizontalHeader()->setVisible(true);

    ui->chtab->verticalHeader()->setVisible(true);

    ui->rttab->resizeColumnsToContents();
    ui->ratab->resizeColumnsToContents();
    ui->chtab->resizeColumnsToContents();
    ui->chtab->verticalHeader()->setMinimumWidth(30);
    ui->crtab->resizeColumnsToContents();

    //***********************************************************
    //********************* Q*Socket client *********************
    //***********************************************************
    //
    for (int i=0; i<f.size(); i++) {			// Считываем массив хостов из XML
        QFile file(f[i]);                       // f[0] - конфигурационный файл 0
        if (!file.open(QIODevice::ReadOnly)) {
            log("MainWindow::MainWindow() config file "+file.fileName()+" error "+ferr[file.error()]);
            continue;
        } else {
            log("MainWindow::MainWindow() config file opened "+file.fileName());
        }

        //***********************************************************
        //**********XML ENGINE II 17.10.2014*************************
        //***********************************************************

        QByteArray data=file.readAll();
        QXmlStreamReader xmlreader(data);
        int j=0;

        while (!xmlreader.error()){
            if (xmlreader.readNextStartElement()){
                QString t=xmlreader.name().toString();
                if (t!="host") continue;

                QXmlStreamAttributes xattr = xmlreader.attributes();
                host[j]=xattr.value("id").toString()+":"+xattr.value("ip").toString()+":"+xattr.value("port").toString();
                log("MainWindow::MainWindow() found "+t+" record "+host[j]);

                //bool ok;
                h = new QStringList(
                            host[j].split(":")
                            );
#ifndef HAVE_QT5
                socket[j] = new Q3Socket(this,h->at(0));
#else
				socket[j] = new QTcpSocket(this);
#endif
                socket[j]->connectToHost(h->at(1),h->at(2).toInt());
                //qDebug()<<"h[1] = "<<h[1]<<" h[0].toUShort(&ok,16) = "<<h[0];
                connect(socket[j], SIGNAL(connected()), SLOT(slotConnected()));
                connect(socket[j], SIGNAL(readyRead()), SLOT(readyRead()));

                log("MainWindow::MainWindow() socket["+QString::number(j)+"]->state() = "+sstate[socket[j]->state()]);
                j++;
            }
        }
        timer_reconnect->start(1000);

        if (xmlreader.atEnd()) {
            log("MainWindow::MainWindow() end of XML file reached");
            continue;
        }

        switch(xmlreader.error()){
        case 0:
            break;
        default:
            log("MainWindow::MainWindow() xml error "+xmlerr[xmlreader.error()]+" at line "+QString::number(xmlreader.lineNumber())+" column "+QString::number(xmlreader.columnNumber()));
            break;
        };
        //***********************************************************
        //***********************************************************
        //***********************************************************

        file.close();
        if (file.error()) {
            log("MainWindow::MainWindow() file "+file.fileName()+" error "+QString::number(file.error()));
        }
    }

    statusBar()->showMessage("Готов", 0);
    //
    this->chdialog = new chDialog();
    this->crdialog = new crDialog();
    this->rtdialog = new rtDialog();
    this->radialog = new raDialog();
}

void MainWindow::slotReconnect()
{
    for(int i=0; i<socket.size(); i++)
    {
        //qDebug("---------------- state = %d",socket[i]->state());
#ifndef HAVE_QT5
        if(socket[i]->state()!= Q3Socket::Connected)
#else
		if(socket[i]->state()!= QTcpSocket::ConnectedState)
#endif
        {
            socket[i]->connectToHost(
			h->at(1),
			h->at(0).toInt()
			);
        }
    }
}

void MainWindow::slotConnected()
{
    for (int j=0; j<socket.size(); j++)
    {
        QString s = "1394_02|CONNECT[TRUE]";
        QByteArray a;

        QDataStream out(&a, QIODevice::WriteOnly);
        //
        out.setVersion(6);
        out<<quint16(0)<<s;
        out.device()->seek(0);
        out<<quint16(a.size() - sizeof(quint16(0)));
#ifndef HAVE_QT5
        socket[j]->writeBlock(
#else
		socket[j]->write(
#endif
			a.data(),
			a.size()
		);
    }

    //    qDebug()<<"============= connected 1394";
}



MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getField(int i)
{
    log("MainWindow::getField("+QString::number(i)+")");
    //
    switch(i)
    {
    case 0:
        return ui->f0->currentText();
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
        return ui->f4->currentText();
        break;
    case 5:
        return ui->f5->text();
        break;
    case 6:
        return ui->f6->text();
    case 7:
        return ui->f7->text();
        break;
    case 8:
        return ui->f8->text();
        break;
    case 9:
        return ui->f9->text();
        break;
    case 10:
        return ui->f10->text();
        break;
    default:
        return "";
        break;
    }
}

void MainWindow::setField(int i,QString v)
{
    log("MainWindow::setField("+QString::number(i)+","+v+")");
    //
    switch(i)
    {
    case 0:
        ui->f0->setCurrentIndex(ui->f0->findText(v));
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
        ui->f4->setCurrentIndex(ui->f4->findText(v));
        break;
    case 5:
        ui->f5->setText(v);
        break;
    case 6:
        ui->f6->setText(v);
        break;
    case 7:
        ui->f7->setText(v);
        break;
    case 8:
        ui->f8->setText(v);
        break;
    case 9:
        ui->f9->setText(v);
        break;
    case 10:
        ui->f10->setText(v);
        break;
    default:
        break;
    }
}

void MainWindow::saveTbl(QTableWidget *tbl)
{
    QString name = "iftab.csv";
    if (tbl) name = tbl->objectName() + ".csv";
    QFile file(name);

    //
    log("MainWindow::saveTbl() file "+name+" opened");
    //

    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data(&file);
        QStringList strList;

        if(!tbl){
            strList.clear();
            for(int i = 0; i<=10; i++) strList << getField(i);
            data << strList.join(";") << "\n";
            file.close();
            return;
        }

        for( int c = 0; c < tbl->columnCount(); ++c )
        {
            strList << tbl->horizontalHeaderItem(c)->data(Qt::DisplayRole).toString();
        }

        data << strList.join(";");
        int rc = tbl->rowCount();
        for( int r = 0; r<rc; ++r )
        {
            strList.clear();
            for( int c = 0; c < tbl->columnCount(); ++c )
            {   QTableWidgetItem* item = tbl->item(r,c);
                if (!item || item->text().isEmpty())
                {
                    tbl->setItem(r,c,new QTableWidgetItem(" "));
                }
                strList << tbl->item(r,c)->text();
            }
            data << "\n" << strList.join(";");
        }
        file.close();
    } else {
        log("MainWindow::saveTbl() file "+name+" error "+ferr[file.error()]);
    }
}

void MainWindow::loadTbl(QTableWidget *tbl)
{
    QString name = "iftab.csv";
    if (tbl) name = tbl->objectName() + ".csv";
    QFile file(name);

    if (!file.open(QFile::ReadOnly)){
        log("MainWindow::loadTbl() file "+name+" error "+ferr[file.error()]);
        file.close();
        return;
    }

    QTextStream data(&file);
    data.setCodec("CP1251");
    data.seek(0);

    QStringList rowData = data.readLine().split(";");
    if (rowData.size()<2) {
        file.close();
        return;
    };

    log("MainWindow::loadTbl() file "+name+" opened");
    if(!tbl)
    {
        for(int i = 0; i<rowData.size(); i++) setField(i, rowData[i]);
        file.close();
        return;
    }

    tbl->clearContents();
    for( int c = 0; c < tbl->columnCount(); ++c )
    {
        tbl->horizontalHeaderItem(c)->setData( Qt::DisplayRole, rowData[c] );
    }

    QStringList s = data.readAll().split("\n");
    tbl->clearContents();
    tbl->setRowCount(s.size());

    for(int r=0; r<s.size(); r++) {
        log("row "+QString::number(r)+" data is "+s[r]);
        rowData = s[r].split(";");
        for (int c = 0; c < rowData.size(); c++)
        {
            tbl->setItem(r,c,new QTableWidgetItem(rowData[c]));
        };
    };

    file.close();
    return;
};

void MainWindow::load(int i)
{
    log("MainWindow::load("+QString::number(i)+")");
    //
    switch(i)
    {
    case 1:
        loadTbl(ui->rttab);
        break;
    case 2:
        loadTbl(ui->ratab);
        break;
    case 3:
        loadTbl(ui->chtab);
        break;
    case 4:
        loadTbl(ui->crtab);
        break;
    default:
        loadTbl(0);
        break;
    }
}


void MainWindow::unload(int i)
{
    log("MainWindow::unload("+QString::number(i)+")");
    switch(i)
    {
    case 1:
        saveTbl(ui->rttab);
        break;
    case 2:
        saveTbl(ui->ratab);
        break;
    case 3:
        saveTbl(ui->chtab);
        break;
    case 4:
        saveTbl(ui->crtab);
        break;
    default:
        saveTbl(0);
        break;
    }
}

int MainWindow::dialog(int i)
{
    log("MainWindow::dialog("+QString::number(i)+")");
    //
    switch(i)
    {
    case 1:
        return rtdialog->exec();
        break;
    case 2:
        return radialog->exec();
        break;
    case 3:
        return chdialog->exec();
        break;
    case 4:
        return crdialog->exec();
        break;
    default:
        return 0;
        break;
    }
}

void MainWindow::newrow(int i)
{
    log("MainWindow::newrow("+QString::number(i)+")");
    //
    switch(i)
    {
    case 1:
        ui->rttab->insertRow(ui->rttab->rowCount());
        break;
    case 2:
        ui->ratab->insertRow(ui->ratab->rowCount());
        break;
    case 3:
        ui->chtab->insertRow(ui->chtab->rowCount());
        break;
    case 4:
        ui->crtab->insertRow(ui->crtab->rowCount());
        break;
    default:
        break;
    }
}

void MainWindow::getrow(int i)
{
    log("MainWindow::getrow("+QString::number(i)+")");
    //
    //int cr;
    int cn;
    QString v = "";

    switch(i)
    {
    case 1:
        //cr=ui->rttab->currentRow();
        cn=ui->rttab->columnCount();
        for (i = 0; i < cn; i++) {
            //qDebug()<<"i="<<i<<" v = "<<v;
            //v = ui->rttab->item(cr,i)->text();
            rtdialog->setField(i,v);
        }
        break;
    case 2:
        //cr=ui->ratab->currentRow();
        cn=ui->ratab->columnCount();
        for (i = 0; i < cn; i++) {
            //v = ui->ratab->item(cr,i)->text();
            radialog->setField(i,v);
        }
        break;
    case 3:
        //cr=ui->chtab->currentRow();
        cn=ui->chtab->columnCount();
        for (i = 0; i < cn; i++) {
            //v = ui->chtab->item(cr,i)->text();
            chdialog->setField(i,v);
        }
        break;
    case 4:
        //cr=ui->crtab->currentRow();
        cn=ui->crtab->columnCount();
        for (i = 0; i < cn; i++) {
            //v = ui->crtab->item(cr,i)->text();
            crdialog->setField(i,v);
        }
        break;
    default:
        break;
    }

}

void MainWindow::updrow(int i)
{
    log("MainWindow::updrow("+QString::number(i)+")");
    //
    int cr;
    int cn;

    switch(i)
    {
    case 1:
        cr=ui->rttab->currentRow();
        cn=ui->rttab->columnCount();
        for (i = 0; i <= cn; i++) {
            QTableWidgetItem *q = new QTableWidgetItem (rtdialog->getField(i));
            ui->rttab->setItem(cr,i,q);
        };
        break;
    case 2:
        cr=ui->ratab->currentRow();
        cn=ui->ratab->columnCount();
        for (i = 0; i <= cn; i++) {
            QTableWidgetItem *q = new QTableWidgetItem (radialog->getField(i));
            ui->ratab->setItem(cr,i,q);
        };
        break;
    case 3:
        cr=ui->chtab->currentRow();
        cn=ui->chtab->columnCount();
        for (i = 0; i <= cn; i++) {
            QTableWidgetItem *q = new QTableWidgetItem (chdialog->getField(i));
            ui->chtab->setItem(cr,i,q);
        };
        break;
    case 4:
        cr=ui->crtab->currentRow();
        cn=ui->crtab->columnCount();
        for (i = 0; i <= cn; i++) {
            QTableWidgetItem *q = new QTableWidgetItem (crdialog->getField(i));
            ui->crtab->setItem(cr,i,q);
        };
        break;
    default:
        break;
    }
}

void MainWindow::delrow(int i)
{
    log("MainWindow::delrow("+QString::number(i)+")");
    //
    int cr;

    switch(i)
    {
    case 1:
        cr=ui->rttab->currentRow();
        ui->rttab->removeRow(cr);
        break;
    case 2:
        cr=ui->ratab->currentRow();
        ui->ratab->removeRow(cr);
        break;
    case 3:
        cr=ui->chtab->currentRow();
        ui->chtab->removeRow(cr);
        break;
    case 4:
        cr=ui->crtab->currentRow();
        ui->crtab->removeRow(cr);
        break;
    default:
        break;
    }
}

void MainWindow::tabdial()
{
    QObject *s = this->sender();
    QString _s = "0x"+s->objectName().right(1);

    statusBar()->showMessage(_s);
    log("MainWindow::tabdial() "+_s);
    int i=ui->tabs->currentIndex();
    bool ok;

    switch(_s.toInt(&ok, 16))
    {
    case 2:
        for (i = 0; i < 5; ++i) unload(i);
        break;
    case 3:
        for (i = 0; i < 5; ++i) load(i);
        break;
    case 5: case 10:
        newrow(i);
        break;
    case 6: case 11:
        if(dialog(i) == QDialog::Accepted) updrow(i);
        break;
    case 7: case 12:
        delrow(i);
        break;
    case 8: case 13:
        load(i);
        break;
    case 9: case 14:
        unload(i);
        break;
    default:
        break;
    }

    //ui->route_tab->insertRow(1);
    //ui->tabs->currentIndex();
    //QTableWidgetItem *i= new QTableWidgetItem ( "test");
    //ui->route_tab->setItem(ui->route_tab->rowCount() - 1,0,i);
}

void MainWindow::log(QString s)
{
    QDate d = QDate::currentDate();
    QTime c = QTime::currentTime();

    int rc = ui->log->rowCount();

    ui->log->insertRow(rc);
    QTableWidgetItem *t= new QTableWidgetItem (d.toString("dd.MM.yy")+" "+c.toString("hh:mm:ss")+" "+s);
    ui->log->setItem(rc,0,t);
    ui->log->resizeColumnsToContents();
}


QString MainWindow::answer(QString q)
{
    log("MainWindow::answer('"+q+"')");

    QString id, a;

    //QMap <QString, QString> tc;

    int v = q.indexOf("[");

    if (v<0) {
        id = q;
    } else id = q.mid(0,v);

    QMap <QString, int> tr;

    tr["STATUS_DEVICE"]=1;
    tr["CONNECT"]=2;
    tr["STATUS_CHANNEL"]=3;
    tr["TABLE_CHANNEL"]=3;
    tr["GET_TABLE_CHANNELS"]=4;

    switch(tr[id]){
    case 1:
        a="1394_02|"+q+"[TRUE]";
        break;
    case 2:
        a=q;
        break;
    case 3:
        a=q+"[1]";
        break;
    case 4:

        a="1394_02|SET_TABLE_CHANNELS";
        for( int r = 0; r < ui->chtab->rowCount(); ++r )
        {
            a+="|BEGIN_LINE|TYPE_CONNECT["+ui->chtab->item(r,3)->text()+"]";
            a+="|SPEED["+ui->chtab->item(r,4)->text()+"]";
            a+="|SIGNAL_LEVEL["+ui->chtab->item(r,5)->text()+"]";
            a+="|MODE["+ui->chtab->item(r,6)->text()+"]";
            a+="|ACCESS["+ui->chtab->item(r,9)->text()+"]";
            a+="|MULTIPLICITY["+ui->chtab->item(r,10)->text()+"]";
        };

        break;
    case 5:
        a="SET_TABLE_CHANNELS";
        break;
    default:
        a="";
        break;
    };

    return a;
}

void MainWindow::readyRead()
{
    log("MainWindow::readyRead() "+QString::number(socket.size())+" sockets");
    for (int j=0; j<socket.size(); j++) {

        // QString s = codec->toUnicode(socket[j]->readAll());
        QString s = socket[j]->readAll();
        s = answer(s);
        if (s=="") continue;
        //
        QByteArray a;
        QDataStream out(&a, QIODevice::WriteOnly);
        //
        out.setVersion(6);
        out<<quint16(0)<<s;
        out.device()->seek(0);
        out<<quint16(a.size() - sizeof(quint16(0)));
#ifndef HAVE_QT5
        socket[j]->writeBlock(
#else
		socket[j]->write(
#endif
			a.data(),
			a.size()
		);
    };
}
