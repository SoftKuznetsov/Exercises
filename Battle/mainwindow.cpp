#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "poolbattle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/logo.png");
    ui->gameLogo->setPixmap(pix);

    client = nullptr;
    server = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonCreate_released()
{
    // create server
    server = new MyTcpServer(this);
    if(server)
        server->start();
    else
        qDebug() << "error memory";

    // hide main window
    hide();

    // show pool for battle
    window = new PoolBattle(server->getSocket(), this);
    window->show();
}


void MainWindow::on_pushButtonConnect_released()
{
    // create client
    client = new MyTcpClient(this);
    if(client)
        client->connectToServer();
    else
        qDebug() << "error memory";

    // hide main window
    hide();

    // show pool for battle
    window = new PoolBattle(client->getSocket(), this);
    window->show();
}
