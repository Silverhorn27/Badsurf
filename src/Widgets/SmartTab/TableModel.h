#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
public:
    TableModel(int nRows, int nColumns, QObject *pobj = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int nRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    int rowCount(const QModelIndex &index) const override;
    int columnCount(const QModelIndex &index) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void appendData(const QVariantList &data);

private:
    int m_nRows;
    int m_nColumns;
    QHash<QModelIndex, QVariant> m_hash;
};

#endif // TABLEMODEL_H
