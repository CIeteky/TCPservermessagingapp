#include "clienthandler.h"
#include <QDataStream>

ClientHandler::ClientHandler(int id, QTcpSocket *socket, QObject *parent)
    : QObject(parent)
    , clientId(id)
    , clientSocket(socket)
    , clientName(QString("Client_%1").arg(id))
{

    connect(clientSocket, &QTcpSocket::readyRead,
            this, &ClientHandler::readMessage);
    connect(clientSocket, &QTcpSocket::disconnected,
            this, &ClientHandler::handleDisconnection);
}

ClientHandler::~ClientHandler()
{
    if (clientSocket) {
        clientSocket->disconnectFromHost();
        clientSocket->deleteLater();
    }
}

void ClientHandler::readMessage()
{
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_5_15);


    if (clientSocket->bytesAvailable() < static_cast<qint64>(sizeof(quint32))) {
        return;
    }

    quint32 blockSize;
    in >> blockSize;

    if (clientSocket->bytesAvailable() < blockSize) {
        return;
    }

    QString message;
    in >> message;


    if (message.startsWith("/name ")) {
        clientName = message.mid(6).trimmed();
        if (clientName.isEmpty()) {
            clientName = QString("Client_%1").arg(clientId);
        }
        return;
    }


    emit messageReceived(clientName, message);
}

void ClientHandler::sendMessage(const QString &message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);


    out << quint32(0);


    out << message;


    out.device()->seek(0);
    out << quint32(block.size() - sizeof(quint32));


    clientSocket->write(block);
}

void ClientHandler::handleDisconnection()
{
    emit clientDisconnected(clientId);
}

void ClientHandler::disconnectClient()
{
    if (clientSocket && clientSocket->state() == QAbstractSocket::ConnectedState) {
        clientSocket->disconnectFromHost();
    }
}
