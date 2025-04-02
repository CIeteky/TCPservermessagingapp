#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , nextClientId(1)
{
    ui->setupUi(this);
    server = new QTcpServer(this);

    setupConnections();
}

MainWindow::~MainWindow()
{
    for (auto thread : clientThreads.values()) {
        thread->quit();
        thread->wait();
    }

    qDeleteAll(clientThreads);
    qDeleteAll(clientHandlers);

    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startServer);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopServer);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::broadcastMessage);

    ui->stopButton->setEnabled(false);
}

void MainWindow::startServer()
{
    int port = ui->portSpinBox->value();

    if (!server->listen(QHostAddress::Any, port)) {
        QMessageBox::critical(this, tr("Server Error"),
                              tr("Unable to start the server: %1.")
                                  .arg(server->errorString()));
        return;
    }

    connect(server, &QTcpServer::newConnection, this, &MainWindow::newConnection);

    ui->statusLabel->setText(tr("Server is running on port %1").arg(port));
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
    ui->portSpinBox->setEnabled(false);

    ui->chatDisplay->append(tr("Server started at %1")
                                .arg(QDateTime::currentDateTime().toString()));
}

void MainWindow::stopServer()
{

    for (auto handler : clientHandlers.values()) {
        handler->disconnectClient();
    }

    server->close();


    disconnect(server, &QTcpServer::newConnection, this, &MainWindow::newConnection);

    ui->statusLabel->setText(tr("Server is stopped"));
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->portSpinBox->setEnabled(true);

    ui->chatDisplay->append(tr("Server stopped at %1")
                                .arg(QDateTime::currentDateTime().toString()));
}

void MainWindow::newConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();
    int clientId = nextClientId++;

    QThread *clientThread = new QThread();
    clientThreads[clientId] = clientThread;


    ClientHandler *handler = new ClientHandler(clientId, clientSocket);
    clientHandlers[clientId] = handler;


    handler->moveToThread(clientThread);


    connect(handler, &ClientHandler::messageReceived,
            this, &MainWindow::displayMessage);
    connect(handler, &ClientHandler::clientDisconnected,
            this, &MainWindow::clientDisconnected);
    connect(clientThread, &QThread::finished,
            handler, &QObject::deleteLater);


    clientThread->start();

    ui->chatDisplay->append(tr("New client connected (ID: %1) at %2")
                                .arg(clientId)
                                .arg(QDateTime::currentDateTime().toString()));
}

void MainWindow::displayMessage(const QString &sender, const QString &message)
{
    QString formattedMessage = QString("[%1] %2: %3")
    .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
        .arg(sender)
        .arg(message);

    ui->chatDisplay->append(formattedMessage);
}

void MainWindow::clientDisconnected(int clientId)
{

    if (clientThreads.contains(clientId)) {
        QThread *thread = clientThreads.take(clientId);
        thread->quit();
        thread->wait();
        delete thread;
    }


    if (clientHandlers.contains(clientId)) {
        clientHandlers.remove(clientId);
    }

    ui->chatDisplay->append(tr("Client disconnected (ID: %1) at %2")
                                .arg(clientId)
                                .arg(QDateTime::currentDateTime().toString()));
}

void MainWindow::broadcastMessage()
{
    QString message = ui->messageInput->text().trimmed();

    if (message.isEmpty()) {
        return;
    }


    displayMessage("Server", message);


    for (auto handler : clientHandlers.values()) {
        handler->sendMessage(message);
    }


    ui->messageInput->clear();
}
