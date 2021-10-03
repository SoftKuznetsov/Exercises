#ifndef POOLBATTLE_H
#define POOLBATTLE_H

#include <QDialog>

#include "board.h"

namespace Ui {
class PoolBattle;
}

class PoolBattle : public QDialog
{
    Q_OBJECT

public:
    explicit PoolBattle(QWidget *parent = nullptr);
    ~PoolBattle();

private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_released();

private:
    Ui::PoolBattle *ui;
    Ship ships;
};

#endif // POOLBATTLE_H
