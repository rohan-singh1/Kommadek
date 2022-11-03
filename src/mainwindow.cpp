#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


#ifdef USE_TEST_DATA_1

    // Test Data #1 as parser is not implemented yet
    QList <QStringList> records;

    int numRows = 25;
    int numColumns = 25;

    for (int i = 1; i <= numRows; i++)
    {
        QStringList row;
        for (int j = 1; j <= numColumns; j++)
        {
            QString cellValue = QString::number(i) + ", " + QString::number(j);
            row.append(cellValue);
        }
        records.append(row);
    }

    KommaTableModel *tableModel =  new KommaTableModel(records, this);
    this->ui->tableView->setModel(tableModel);

#endif

#ifdef USE_TEST_DATA_2

    // Test Data #2 as parser is not implemented yet
    QList <QStringList> stringMatrix  = {{"A", "B", "C", "D"}, {"Alpha", "Bravo", "Charlie", "Delta"}, {"1", "2", "3", "4", "5"}};

    KommaTableModel *tableModel =  new KommaTableModel(stringMatrix, this);
    this->ui->tableView->setModel(tableModel);

#endif

}

MainWindow::~MainWindow()
{
    delete ui;
}

