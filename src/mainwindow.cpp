#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->stackedWidget->setCurrentIndex(0); // Setting the start page as the default page on startup
    _tableModel = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleTableMetadataUpdateSignal()
{
    QString statusMessage = "Rows: " +
        QString::number(_tableModel->rowCount()) + " | Columns: " +
        QString::number(_tableModel->columnCount()) + " | Total Cells: " +
        QString::number(_tableModel->rowCount() * _tableModel->columnCount()) + " | Filled Cells: " +
        QString::number(_tableModel->filledCellCount()) + " | Empty Cells: " +
        QString::number(_tableModel->emptyCellCount());

    ui->statusbar->showMessage(statusMessage);
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open CSV File"), "", tr("CSV Files (*.csv)"));

    CsvParser *csvParser = new CsvParser(this);
    auto lines = csvParser->readAllLines(fileName);
    auto stringMatrix  = csvParser->parseCsvData(lines);
    _tableModel =  new KommaTableModel(stringMatrix, this);
    connect(_tableModel, SIGNAL(tableMetadataUpdateSignal()), SLOT(handleTableMetadataUpdateSignal()));
    if(!stringMatrix.empty())
    {

        this->ui->tableView->setModel(_tableModel);
        this->ui->stackedWidget->setCurrentIndex(1);
        handleTableMetadataUpdateSignal();
    }   
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
    on_actionQuit_triggered();
}

