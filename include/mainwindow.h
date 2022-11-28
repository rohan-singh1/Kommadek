#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include "kommatablemodel.h"
#include "csvparser.h"
#include "csvexporter.h"
#include "aboutdialog.h"
#include "helpdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString getTitleFromFileNameWithPath(QString);

private slots:
    void handleTableMetadataUpdateSignal();

    void handleDataChanged(const QModelIndex, const QModelIndex, const QVector<int>);

    void saveFile(QString);

    void updateWindowTitle(QString);

    void initColumnContextMenu();

    void initRowContextMenu();

    void handleColumnCustomMenuRequested(const QPoint&);

    void handleRowCustomMenuRequested(const QPoint&);

    void insertColumnRight();

    void insertColumnLeft();

    void insertRowTop();

    void insertRowBottom();

    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_openButton_clicked();

    void on_quitButton_clicked();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

private:
    Ui::MainWindow *ui;

    KommaTableModel *_tableModel;
    QString _fileNameWithPath;
    const QString _titlePrefix = "Kommadek";
    QMenu *_columnMenu;
    QMenu *_rowMenu;
    QModelIndex _currentIndexForContextMenu;
};
#endif // MAINWINDOW_H
