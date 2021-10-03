#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "poolbattle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonCreate_released();

    void on_pushButtonConnect_released();

private:
    Ui::MainWindow *ui;
    PoolBattle * window;
};
#endif // MAINWINDOW_H
