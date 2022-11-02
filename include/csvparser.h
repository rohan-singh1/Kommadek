#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QObject>

class CsvParser : public QObject
{
    Q_OBJECT
public:
    explicit CsvParser(QObject *parent = nullptr);

signals:

};

#endif // CSVPARSER_H
