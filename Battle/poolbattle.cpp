#include "poolbattle.h"
#include "ui_poolbattle.h"
#include <QMessageBox>

PoolBattle::PoolBattle(QTcpSocket * sock, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PoolBattle)
{
    my_socket = sock;
    ui->setupUi(this);
    ui->tableWidget_2->setEnabled(false);
}

PoolBattle::~PoolBattle()
{
    delete ui;
}

void PoolBattle::on_tableWidget_cellClicked(int row, int column)
{
    QTableWidgetItem * itm = new QTableWidgetItem();
    itm = ui->tableWidget->currentItem();
    if (itm != nullptr) {
        if (itm->background() == Qt::green)
            return;
    }

    if (ships.setCell(row, column) != RESULT_OK) {
        QMessageBox::information(this, "Info", "Couldn't add ship!");
        return;
    }

    QTableWidgetItem * item = new QTableWidgetItem();
    item->setBackground(Qt::green);
    ui->tableWidget->setItem(row, column, item);
}


void PoolBattle::on_pushButton_released()
{
    if (ships.checkShips() != RESULT_OK) {
        QMessageBox::information(this, "Info", "You need to have: \n 1 ship with 4-cells, \n 2 ships with 3-cells, \n 3 ships with 2-cells, \n 4 ships with 1-cell!");
        return;
    }

    ui->tableWidget_2->setEnabled(true);
}


void PoolBattle::on_tableWidget_2_cellClicked(int row, int column)
{
    // send request
    QByteArray buff;
    buff.resize(2);
    buff[0] = row;
    buff[1] = column;
//    QString str = QString::number(row) + QString::number(column);
//    my_socket->write(str.data(), str.length());
    my_socket->write(buff);

    // read response
    // show result

    QTableWidgetItem * item = new QTableWidgetItem();

    // test analysis pool of ship oponent
    if (ships.isFullCell(row, column))
        item->setBackground(Qt::blue);
    else
        item->setBackground(Qt::red);

    ui->tableWidget_2->setItem(row, column, item);
}

