#include <mytcpclient.h>
#include <QDebug>

MyTcpClient::MyTcpClient(QObject * parent) : QObject(parent) {
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &MyTcpClient::socketRead);
    connect(socket, &QTcpSocket::disconnected, this, &MyTcpClient::socketDisconnect);
}

void MyTcpClient::connectToServer() {
    socket->connectToHost("127.0.0.1", 6000);

    if (socket->waitForConnected(500)) {
        qDebug() << "connect";
    } else {
        qDebug() << "fail connect";
    }
}

void MyTcpClient::socketRead() {
    while(socket->bytesAvailable()>0) {
        message = socket->readAll();
        qDebug() << message;
    }
    socket->write("apply your message!");
}

void MyTcpClient::socketDisconnect() {
    socket->deleteLater();
}

QTcpSocket* MyTcpClient::getSocket() {
    return socket;
}

