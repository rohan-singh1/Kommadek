#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add spacer in toolbar between Save As and Help buttons
    QWidget* spacer = new QWidget(ui->toolBar);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->toolBar->insertWidget(ui->actionHelp,spacer);

    ui->actionSave->setEnabled(false);
    ui->actionSave_As->setEnabled(false);

    ui->stackedWidget->setCurrentIndex(1); // Setting the table viewer page as the default page on startup
    _tableModel = nullptr;


    initColumnContextMenu();
    initRowContextMenu();
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
        ui->actionSave->setEnabled(true);
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

        updateWindowTitle(getTitleFromFileNameWithPath(file_name_with_path));
        ui->actionSave->setEnabled(false);
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

void MainWindow::initColumnContextMenu()
{
    QHeaderView* headerView = ui->tableView->horizontalHeader();
    headerView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(headerView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(handleColumnCustomMenuRequested(const QPoint&)));

    _columnMenu = new QMenu(ui->tableView);
    QAction *insertRight = _columnMenu->addAction("Insert Column to the Right");
    QAction *insertLeft = _columnMenu->addAction("Insert Column to the Left");

    connect(insertRight, SIGNAL(triggered()), this, SLOT(insertColumnRight()));
    connect(insertLeft, SIGNAL(triggered()), this, SLOT(insertColumnLeft()));
}

void MainWindow::initRowContextMenu()
{

    QHeaderView* headerView = ui->tableView->verticalHeader();
    headerView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(headerView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(handleRowCustomMenuRequested(const QPoint&)));

    _rowMenu = new QMenu(ui->tableView);
    QAction *insertTop = _rowMenu->addAction("Insert Row to the Top");
    QAction *insertBottom = _rowMenu->addAction("Insert Row to the Bottom");

    connect(insertTop, SIGNAL(triggered()), this, SLOT(insertRowTop()));
    connect(insertBottom, SIGNAL(triggered()), this, SLOT(insertRowBottom()));
}

void MainWindow::handleColumnCustomMenuRequested(const QPoint& mouse_position)
{
    _currentIndexForContextMenu = ui->tableView->indexAt(mouse_position);
    _columnMenu->popup(ui->tableView->viewport()->mapToGlobal(mouse_position));
}

void MainWindow::handleRowCustomMenuRequested(const QPoint & mouse_position)
{
    _currentIndexForContextMenu = ui->tableView->indexAt(mouse_position);
    _rowMenu->popup(ui->tableView->viewport()->mapToGlobal(mouse_position));
}

void MainWindow::insertColumnRight()
{
    _tableModel->insertEmptyColumn(_currentIndexForContextMenu.column() + 1);
    ui->tableView->setModel(nullptr);
    ui->tableView->setModel(_tableModel);
}

void MainWindow::insertColumnLeft()
{
    _tableModel->insertEmptyColumn(_currentIndexForContextMenu.column());
    ui->tableView->setModel(nullptr);
    ui->tableView->setModel(_tableModel);
}

void MainWindow::insertRowTop()
{
    _tableModel->insertEmptyRow(_currentIndexForContextMenu.row());
    ui->tableView->setModel(nullptr);
    ui->tableView->setModel(_tableModel);
}

void MainWindow::insertRowBottom()
{
    _tableModel->insertEmptyRow(_currentIndexForContextMenu.row() + 1);
    ui->tableView->setModel(nullptr);
    ui->tableView->setModel(_tableModel);
}

void MainWindow::on_actionOpen_triggered()
{
    _fileNameWithPath = QFileDialog::getOpenFileName(this,tr("Open CSV File"), "", tr("CSV Files (*.csv)"));
    QFile fileNameWithPath(_fileNameWithPath);
    if(fileNameWithPath.exists())
    {
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

            ui->tableView->setModel(_tableModel);
            ui->stackedWidget->setCurrentIndex(1);
            ui->actionSave_As->setEnabled(true);
            handleTableMetadataUpdateSignal();
            updateWindowTitle(getTitleFromFileNameWithPath(_fileNameWithPath));
        }
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
    AboutDialog aboutDialog;
    aboutDialog.exec();
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
