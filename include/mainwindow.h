#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include "kommatablemodel.h"
#include "csvparser.h"
#include "csvexporter.h"

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

    KommaTableModel* _tableModel;
    QString _fileNameWithPath;
    const QString _titlePrefix = "Kommadek";
};
#endif // MAINWINDOW_H
