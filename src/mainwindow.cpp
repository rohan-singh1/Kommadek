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

QString MainWindow::getTitleFromFileNameWithPath(QString file_name_with_path)
{
    QFile file (file_name_with_path);
    QFileInfo fileInfo(file.fileName());
    QString fileName(fileInfo.fileName());
    return _titlePrefix + " - " + fileName;
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

void MainWindow::handleDataChanged(const QModelIndex topLeft, const QModelIndex bottomRight, const QVector<int> roles)
{
    Q_UNUSED(topLeft);          // Parameter not required
    Q_UNUSED(bottomRight);      // Parameter not required
    Q_UNUSED(roles);            // Parameter not required

    if(!this->windowTitle().endsWith("*"))
    {
        this->setWindowTitle(this->windowTitle() + "*");
    }

}

void MainWindow::saveFile(QString file_name_with_path)
{
    CsvExporter *csvExporter = new CsvExporter(this);
    bool isFileSaveSuccessful = csvExporter->exportToCsvFile(_tableModel->stringMatrix(), file_name_with_path);

    if (isFileSaveSuccessful)
    {
        qDebug() << "File save successful!";
        _fileNameWithPath = file_name_with_path;

        if(this->windowTitle().endsWith("*"))
        {
            updateWindowTitle(getTitleFromFileNameWithPath(file_name_with_path));
        }
    }
    else
    {
        qDebug() << "File save failed!";
    }
}

void MainWindow::updateWindowTitle(QString new_caption)
{
    this->setWindowTitle(new_caption);
}


void MainWindow::on_actionOpen_triggered()
{
    _fileNameWithPath = QFileDialog::getOpenFileName(this,tr("Open CSV File"), "", tr("CSV Files (*.csv)"));

    CsvParser *csvParser = new CsvParser(this);
    auto lines = csvParser->readAllLines(_fileNameWithPath);
    auto stringMatrix  = csvParser->parseCsvData(lines);

    // Freeing up memory in case a file had been loaded previously
    if(_tableModel)
    {
        delete _tableModel;
        _tableModel = nullptr;
    }

    _tableModel =  new KommaTableModel(stringMatrix, this);
    connect(_tableModel, SIGNAL(tableMetadataUpdateSignal()), SLOT(handleTableMetadataUpdateSignal()));
    connect(_tableModel, SIGNAL(dataChanged(const QModelIndex, const QModelIndex, const QVector<int>)),
                                this, SLOT(handleDataChanged(const QModelIndex, const QModelIndex, const QVector<int>)));
    if(!stringMatrix.empty())
    {

        this->ui->tableView->setModel(_tableModel);
        this->ui->stackedWidget->setCurrentIndex(1);
        handleTableMetadataUpdateSignal();
        updateWindowTitle(getTitleFromFileNameWithPath(_fileNameWithPath));
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


void MainWindow::on_actionSave_triggered()
{
    saveFile(_fileNameWithPath);
}


void MainWindow::on_actionSave_As_triggered()
{
    QString fileNameWithPath = QFileDialog::getSaveFileName(this,tr("Save CSV File"), "", tr("CSV Files (*.csv)"));
    saveFile(fileNameWithPath);
}

