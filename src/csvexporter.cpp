#include "csvexporter.h"

CsvExporter::CsvExporter(QObject *parent) : QObject(parent)
{

}

bool CsvExporter::exportToCsvFile(QList<QStringList> string_matrix, QString file_name_with_path)
{
    bool isSuccessful = false;
    QString fileNameWithPath = file_name_with_path;
    if (!fileNameWithPath.endsWith(".CSV", Qt::CaseInsensitive))
    {
        fileNameWithPath.append(".csv");
    }

    QFile file(fileNameWithPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return isSuccessful;
    }

    else
    {
        QTextStream outStream(&file);
        outStream << serializeStringMatrix(string_matrix);
        isSuccessful = true;
    }
    file.close();
    return isSuccessful;
}

QString CsvExporter::serializeStringMatrix(QList<QStringList> string_matrix)
{
    QStringList row;
    QString processedOutputString;

    foreach (row, string_matrix)
    {
        QString cell, processedRow;
        foreach (cell, row)
        {
            processedRow += cell + ",";
        }
        processedRow.chop(1);           // Removing final comma
        processedRow.append("\n");
        processedOutputString.append(processedRow);
    }
    processedOutputString.chop(1);      // Removing final line break
    return processedOutputString;
}
