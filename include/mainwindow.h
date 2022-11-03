#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define USE_TEST_DATA_1
// #define USE_TEST_DATA_2  // Using Test Data 1

#include <QMainWindow>
#include "kommatablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
