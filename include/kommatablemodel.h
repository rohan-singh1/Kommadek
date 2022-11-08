#ifndef KOMMATABLEMODEL_H
#define KOMMATABLEMODEL_H

#include <QAbstractTableModel>
#include <QDebug>

class KommaTableModel : public QAbstractTableModel
{
    Q_OBJECT

signals:
    void tableMetadataUpdateSignal();

private:
    QList <QStringList> _stringMatrix;
    QList <int> _rowSizes;

    int _rowCount;
    int _columnCount;
    int _filledCellCount;

public:
    explicit KommaTableModel(QList <QStringList> stringMatrix, QObject *parent = nullptr);


    // Overriding QAbstractTableModel virtual functions to use in my custom table model class

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;


    // To make the model editable

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;


    // Assorted utility functions for my table model

    int maxColumns();
    int filledCellCount() const;
    int emptyCellCount() const;
    int updateFilledCellsCount();
    void updateRowSizes(int row_number, int new_size);
    QList <int> initRowSizes();

public slots:
    void updateTableMetadata(QModelIndex, QModelIndex);
};

#endif // KOMMATABLEMODEL_H
