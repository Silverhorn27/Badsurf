#include "TableModel.h"

TableModel::TableModel(int nRows, int nColumns, QObject *pobj)
    : QAbstractTableModel(pobj)
    , m_nRows(nRows)
    , m_nColumns(nColumns)
{

}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("ID");
        case 1:
            return QString("Name");
        case 2:
            return QString("VAL");
        case 3:
            return QString("Wrst");
        case 4:
            return QString("Tresh");
        case 5:
            return QString("Raw");
        case 6:
            return QString("Health");
        }
    }
    return QVariant();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    QString str = QString("%1,%2").arg(index.row() + 1).arg(index.column() + 1);
    return role == Qt::DisplayRole ? m_hash.value(index)
                                    : QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_hash[index] = value;
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

int TableModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return m_nRows;
}

int TableModel::columnCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return m_nColumns;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index);
}

void TableModel::appendData(const QVariantList &data)
{
    insertRow(rowCount(QModelIndex()));

    foreach(const QVariant &item, data)
        setData(createIndex(rowCount(QModelIndex()), 0), item, Qt::EditRole);
}
