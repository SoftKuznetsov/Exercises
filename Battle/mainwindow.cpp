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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonCreate_released()
{
    // create server

    // hide main window
    hide();

    // show pool for battle
    window = new PoolBattle(this);
    window->show();
}


void MainWindow::on_pushButtonConnect_released()
{
    // create client
    // find server
}

