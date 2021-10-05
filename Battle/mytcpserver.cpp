#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer(parent) {}

void MyTcpServer::start() {
    connect(this, &QTcpServer::newConnection, this, &MyTcpServer::newConnection);

    if(this->listen(QHostAddress::Any, 6000)){
        qDebug() << "server is started";
    } else {
        qDebug() << "server is not started";
    }
}

void MyTcpServer::newConnection() {
    while (this->hasPendingConnections())
        appendToSocketList(this->nextPendingConnection());
}

void MyTcpServer::appendToSocketList(QTcpSocket* sock) {
    socket = sock;

    connect(socket, &QTcpSocket::readyRead, this, &MyTcpServer::socketRead);
    connect(socket, &QTcpSocket::disconnected, this, &MyTcpServer::socketDisconnect);

    qDebug() << "client connected!";
    socket->write("connect success!");
}

//void MyTcpServer::incomingConnection(int socket_desriptor) {
//    socket = new QTcpSocket(this);
//    socket->setSocketDescriptor(socket_desriptor);

//    socket->write("You are connect!\r\n");
//    qDebug() << "client connected!";

//    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReady));
//    connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnect));
//}

void MyTcpServer::socketRead() {
    while(socket->bytesAvailable()>0) {
        message = socket->readAll();
        qDebug() << message;
    }
}

void MyTcpServer::socketDisconnect() {
    qDebug() << "disconnect";
    socket->deleteLater();
}

QTcpSocket* MyTcpServer::getSocket() {
    return socket;
}
