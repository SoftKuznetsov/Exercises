#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent) {
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if(!server->listen(QHostAddress::Any, 6000)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection()
{
    socket = server->nextPendingConnection();

    socket->write("Hello, World!!! I am echo server!\r\n");

    connect(socket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(socket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotServerRead()
{
    while(socket->bytesAvailable()>0)
    {
        QByteArray array = socket->readAll();

        // echo
        socket->write(array);
    }
}

void MyTcpServer::slotClientDisconnected()
{
    socket->close();
}
