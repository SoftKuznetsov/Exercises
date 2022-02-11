#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class MyTcpServer : public QTcpServer {
    Q_OBJECT

public:
    explicit MyTcpServer(QObject * parent = 0);    

public slots:
    void start();
    void newConnection();
    void appendToSocketList(QTcpSocket* sock);
//    void incomingConnection(int socket_desriptor);
    void socketRead();
    void socketDisconnect();

    QTcpSocket* getSocket();
private:
    QTcpSocket * socket;
    QByteArray message;
};

#endif // MYTCPSERVER_H
