#include "clienthandler.h"
#include <QDataStream>
#include <QDebug>

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
    QByteArray data = clientSocket->readAll();
    buffer.append(data);

    while (true) {
        int newlineIndex = buffer.indexOf('\n');
        if (newlineIndex != -1) {
            QByteArray rawLine = buffer.left(newlineIndex).trimmed();
            buffer.remove(0, newlineIndex + 1);

            QString message = QString::fromUtf8(rawLine);

            if (message.startsWith("/name ")) {
                clientName = message.mid(6).trimmed();
                if (clientName.isEmpty()) {
                    clientName = QString("Client_%1").arg(clientId);
                }
                continue;
            }

            emit messageReceived(clientName, message);
            continue;
        }

        if (buffer.size() < static_cast<int>(sizeof(quint32))) {
            return;
        }

        QDataStream in(&buffer, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_15);
        in.device()->seek(0);

        quint32 blockSize;
        in >> blockSize;

        if (buffer.size() < static_cast<int>(sizeof(quint32) + blockSize)) {
            return;
        }

        QString message;
        in >> message;

        buffer.remove(0, sizeof(quint32) + blockSize);

        if (message.startsWith("/name ")) {
            clientName = message.mid(6).trimmed();
            if (clientName.isEmpty()) {
                clientName = QString("Client_%1").arg(clientId);
            }
            continue;
        }

        emit messageReceived(clientName, message);
    }
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
