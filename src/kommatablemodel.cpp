#include "include/kommatablemodel.h"

KommaTableModel::KommaTableModel(QList <QStringList> string_matrix, QObject *parent) : QAbstractTableModel(parent)
{
    connect(this, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(updateTableMetadata(QModelIndex, QModelIndex)));
    _stringMatrix = string_matrix;
    _rowSizes = initRowSizes();
    _filledCellCount = updateFilledCellsCount();
    updateTableMetadata(QModelIndex(),QModelIndex());
}

int KommaTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);               // Parameter not required
    return _rowCount;
}

int KommaTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);               // Parameter not required
    return _columnCount;
}

QVariant KommaTableModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
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
        // Will implement it as a customizable option if user wants
        // the first row of the CSV data to be shown as the header.
        // Displaying just column number in the meantime.

        // return _stringMatrix.at(0).at(section);

        return QString::number(section + 1);
    }
    else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    {
        return QString::number(section + 1);
    }
    else
    {
        return QVariant();
    }
}

Qt::ItemFlags KommaTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool KommaTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        QStringList row  = _stringMatrix.at(index.row());
        int currentColumn = index.column();

        if (currentColumn > row.size() - 1)
        {
            while (currentColumn > row.size())
            {
                row.append("");
            }
            row.append(value.toString());
        }
        else
        {
            row.replace(index.column(), value.toString());
        }

        QString cell;
        int newRowSize = 0;
        foreach(cell, row)
        {
            if (cell!= "")
            {
                newRowSize++;
            }
        }

        updateRowSizes(index.row(), newRowSize);
        _stringMatrix.replace(index.row(), row);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

int KommaTableModel::maxColumns()
{
    int maxColumns = 0;
    QStringList row;

    foreach(row, _stringMatrix)
    {
        int rowSize  = row.size();
        maxColumns = rowSize > maxColumns ? rowSize : maxColumns;
    }
    return maxColumns;
}

int KommaTableModel::filledCellCount() const
{
    return _filledCellCount;
}

int KommaTableModel::emptyCellCount() const
{
    return (_rowCount * _columnCount) - _filledCellCount;
}

int KommaTableModel::updateFilledCellsCount()
{
    int sum = 0, i = 0;
    foreach(i, _rowSizes)
    {
        sum += i;
    }
    return sum;
}

void KommaTableModel::updateRowSizes(int row_number, int new_size)
{
    _rowSizes.replace(row_number, new_size);
    _filledCellCount = updateFilledCellsCount();
}

void KommaTableModel::insertEmptyRow(int position)
{
    QStringList stringList;

    for (int i = 0; i < maxColumns(); i++)
    {
        stringList.append("");
    }
    _stringMatrix.insert(position, stringList);
    emit dataChanged(index (position, 0), index(position, maxColumns()));
    _rowSizes = initRowSizes();
}

void KommaTableModel::insertEmptyColumn(int position)
{
    for (int i = 0; i < _stringMatrix.size(); i++)
    {
        if (position > _stringMatrix[i].size())
        {
            for (int j = 0; j < (position -_stringMatrix[i].size()); j++)
            {
                _stringMatrix[i].append("");
            }
        }
        _stringMatrix[i].insert(position, "");
    }

    emit dataChanged(index (0, position), index(rowCount(), maxColumns()));
    _columnCount = maxColumns();
}

QList <int> KommaTableModel::initRowSizes()
{
    QList <int> rowSizesLocal;
    QStringList row;
    foreach(row, _stringMatrix)
    {
        QString cell;
        int rowSize = 0;
        foreach(cell, row)
        {
            if (cell!= "")
            {
                rowSize++;
            }
        }
        rowSizesLocal.append(rowSize);
    }
    return rowSizesLocal;
}

QList<QStringList> KommaTableModel::stringMatrix()
{
    return _stringMatrix;
}

void KommaTableModel::updateTableMetadata(QModelIndex bottom_left, QModelIndex top_right)
{
    Q_UNUSED(bottom_left);      // Parameter not required
    Q_UNUSED(top_right);        // Parameter not required

    _rowCount = _stringMatrix.size();
    _columnCount = maxColumns();
    _filledCellCount = filledCellCount();

    emit tableMetadataUpdateSignal();
}
