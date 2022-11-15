#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class CsvExporter : public QObject
{
    Q_OBJECT

private:
    QList <QStringList> _stringMatrix;

public:
    explicit CsvExporter(QObject *parent = nullptr);

    bool exportToCsvFile(QList <QStringList> string_matrix, QString file_name_with_path);

    QString serializeStringMatrix(QList <QStringList> string_matrix);

signals:

};

#endif // CSVEXPORTER_H
