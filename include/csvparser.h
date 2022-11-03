#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class CsvParser : public QObject
{
    Q_OBJECT

private:
    QStringList _allLines;

public:
    explicit CsvParser(QObject *parent = nullptr);

    QStringList readAllLines(QString file_name_with_path);
    QList <QStringList> parseCsvData(QStringList csv_lines);

signals:

};

#endif // CSVPARSER_H
