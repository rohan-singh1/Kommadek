#include "kommatablemodel.h"

KommaTableModel::KommaTableModel(QList <QStringList> string_matrix, QObject *parent) : QAbstractTableModel(parent)
{
    _stringMatrix = string_matrix;
}

int KommaTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);               // Parameter not required
    return _stringMatrix.size();
}

int KommaTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);               // Parameter not required
    return getMaxColumns();
}

QVariant KommaTableModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole)
    { 
        QStringList row = _stringMatrix.at(index.row());

        if (row.size() > (index.column())) // To check if a column does not contain any data for a particular row
        {
            QString cellString = _stringMatrix.at(index.row()).at(index.column());
            return cellString;
        }
        else
        {
            return QVariant();
        }
    }
    else
    {
        return QVariant();
    }
}

QVariant KommaTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return _stringMatrix.at(0).at(section);
    }
    else
    {
        return QVariant();
    }
}

int KommaTableModel::getMaxColumns() const
{
    int maxColumns = 0;
    QStringList row;

    foreach(row, _stringMatrix)
    {
        maxColumns = row.size() > maxColumns ? row.size() : maxColumns;
    }

    return maxColumns;
}
