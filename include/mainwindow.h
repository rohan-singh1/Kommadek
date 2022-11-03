#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #define USE_TEST_DATA_1
// #define USE_TEST_DATA_2

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include "kommatablemodel.h"
#include "csvparser.h"

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
    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_openButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
