#ifndef POOLBATTLE_H
#define POOLBATTLE_H

#include <QDialog>

#include "board.h"
#include "mytcpclient.h"
#include "mytcpserver.h"

namespace Ui {
class PoolBattle;
}

class PoolBattle : public QDialog
{
    Q_OBJECT

public:
    explicit PoolBattle(QTcpSocket * sock, QWidget *parent = nullptr);
    ~PoolBattle();

private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_released();

    void on_tableWidget_2_cellClicked(int row, int column);

private:
    Ui::PoolBattle *ui;
    Ship ships;

    QTcpSocket * my_socket;
};

#endif // POOLBATTLE_H
