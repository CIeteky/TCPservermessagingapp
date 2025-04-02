#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QList>
#include <QThread>
#include "clienthandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startServer();
    void stopServer();
    void newConnection();
    void displayMessage(const QString &sender, const QString &message);
    void clientDisconnected(int clientId);
    void broadcastMessage();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QMap<int, QThread*> clientThreads;
    QMap<int, ClientHandler*> clientHandlers;
    int nextClientId;

    void setupConnections();
};
#endif
