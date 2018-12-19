#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//
//#include "disrep.h"
#include <QMainWindow>
#include <QTableWidget>
//
#include "chdialog.h"
#include "crdialog.h"
#include "radialog.h"
#include "rtdialog.h"
//
#ifndef HAVE_QT5
#include <Q3Socket>
static const QStringList sstate  = QStringList() << "Q3Socket::Idle" << "Q3Socket::HostLookup" << "Q3Socket::Connecting" << "Q3Socket::Connected" << "Q3Socket::Closing";
#endif

#ifdef HAVE_QT5
#include <QTcpSocket>
static const QStringList sstate  = QStringList() << "QAbstractSocket::UnconnectedState" << "QAbstractSocket::HostLookupState" << "QAbstractSocket::ConnectingState" << "QAbstractSocket::ConnectedState" << "QAbstractSocket::BoundState" << "QAbstractSocket::ClosingState" << "QAbstractSocket::ListeningState";
#endif
//
static const QStringList f  = QStringList() << "config.xml";
static const QStringList ferr  = QStringList() << "QFile::NoError" << "QFile::ReadError" << "QFile::WriteError" << "QFile::FatalError" << "QFile::ResourceError" << "QFile::OpenError" << "QFile::AbortError" << "QFile::TimeOutError" << "QFile::UnspecifiedError" << "QFile::RemoveError" << "QFile::RenameError" << "QFile::PositionError" << "QFile::ResizeError" << "QFile::PermissionsError" << "QFile::CopyError";
static const QStringList xmlerr  = QStringList() << "QXmlStreamReader::NoError" << "QXmlStreamReader::CustomError" << "QXmlStreamReader::NotWellFormedError" << "QXmlStreamReader::PrematureEndOfDocumentError" << "QXmlStreamReader::UnexpectedElementError";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //
    //disrep* dis;

private slots:
    void saveTbl(QTableWidget *tbl);
    void loadTbl(QTableWidget *tbl);
    void slotConnected();
    void load(int i);
    void unload(int i);
    void tabdial();

    int dialog(int i);

    void newrow(int i);
    void getrow(int i);
    void updrow(int i);
    void delrow(int i);

    QString getField(int i);
    void setField(int i, QString v);

    void log(QString s);
    void readyRead();
    QString answer(QString q);

    void slotReconnect();

private:
    Ui::MainWindow *ui;
    QStringList* h;
    QTimer* timer_reconnect;
    //
    chDialog* chdialog;
    crDialog* crdialog;
    raDialog* radialog;
    rtDialog* rtdialog;
    //
#ifdef HAVE_QT5
    QList<QString> host;		// Массив параметров хостов для обмена
    QList<QTcpSocket*> socket;  // Массив сокетов
#else
    QList<QString> host;		// Массив параметров хостов для обмена
    QList<Q3Socket*> socket;    // Массив сокетов
#endif
 };

#endif // MAINWINDOW_H
