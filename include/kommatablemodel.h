#ifndef KOMMATABLEMODEL_H
#define KOMMATABLEMODEL_H

#include <QAbstractTableModel>

class KommaTableModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    QList <QStringList> _stringMatrix;
    int _rowCount;
    int _columnCount;
    int _cellCount;

public:
    explicit KommaTableModel(QList <QStringList> stringMatrix, QObject *parent = nullptr);

    // Overriding QAbstractTableModel virtual functions to use in my custom table model class

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;


    // Assorted utility functions for my table model

    int maxColumns();
    int cellCount() const;
};

#endif // KOMMATABLEMODEL_H
