#include "csvparser.h"

CsvParser::CsvParser(QObject *parent) : QObject(parent)
{

}

QStringList CsvParser::readAllLines(QString file_name_with_path)
{
    QFile file(file_name_with_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return _allLines;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        _allLines.append(line);
    }
    return _allLines;
}

QList<QStringList> CsvParser::parseCsvData(QStringList csv_lines)
{
    QList <QStringList> parsedData;

    QString cell;
    foreach (cell, csv_lines)
    {
        QStringList row = cell.split(u',', Qt::SkipEmptyParts);
        parsedData.append(row);
    }

    return parsedData;
}
