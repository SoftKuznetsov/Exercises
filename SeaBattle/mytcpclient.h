#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QMessageBox>

class MyTcpClient : public QObject {

    Q_OBJECT

public:
    explicit MyTcpClient(QObject * parent = 0);

public slots:
    void connectToServer();
    void socketRead();
    void socketDisconnect();

    QTcpSocket* getSocket();
private:
    QTcpSocket * socket;
    QByteArray message;
};

#endif // MYTCPCLIENT_H
