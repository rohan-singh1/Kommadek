#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->stackedWidget->setCurrentIndex(0);


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
    this->ui->stackedWidget->setCurrentIndex(1);

#endif

#ifdef USE_TEST_DATA_2

    // Test Data #2 as parser is not implemented yet
    QList <QStringList> stringMatrix  = {{"A", "B", "C", "D"}, {"Alpha", "Bravo", "Charlie", "Delta"}, {"1", "2", "3", "4", "5"}};

    KommaTableModel *tableModel =  new KommaTableModel(stringMatrix, this);
    this->ui->tableView->setModel(tableModel);
    this->ui->stackedWidget->setCurrentIndex(1);

#endif

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open CSV File"), "", tr("CSV Files (*.csv)"));

    CsvParser *csvParser = new CsvParser(this);
    auto lines = csvParser->readAllLines(fileName);
    auto stringMatrix  = csvParser->parseCsvData(lines);
    KommaTableModel *tableModel =  new KommaTableModel(stringMatrix, this);

    if(!stringMatrix.empty())
    {

        this->ui->tableView->setModel(tableModel);
        this->ui->stackedWidget->setCurrentIndex(1);
    }

    QString statusMessage = "Rows: " +
        QString::number(tableModel->rowCount()) + " | Columns: " +
        QString::number(tableModel->columnCount()) + " | Total Cells: " +
        QString::number(tableModel->rowCount() * tableModel->columnCount()) + " | Filled Cells: " +
        QString::number(tableModel->cellCount()) + " | Empty Cells: " +
        QString::number((tableModel->rowCount() * tableModel->columnCount()) - tableModel->cellCount());

    ui->statusbar->showMessage(statusMessage);
}


void MainWindow::on_actionQuit_triggered()
{
    exit(0);
}


void MainWindow::on_actionHelp_triggered()
{

}


void MainWindow::on_actionAbout_triggered()
{

}


void MainWindow::on_openButton_clicked()
{
    on_actionOpen_triggered();
}


void MainWindow::on_quitButton_clicked()
{
    exit(0);
}

