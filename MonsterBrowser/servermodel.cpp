#include "servermodel.h"


ServerModel::ServerModel(QObject* parent) : QAbstractItemModel(parent)
{

}


QModelIndex ServerModel::index(int row, int column, const QModelIndex&) const
{
    return createIndex(row, column);
}


QModelIndex ServerModel::parent(const QModelIndex&) const
{
    return QModelIndex();
}


int ServerModel::rowCount(const QModelIndex&) const
{
    return 100'000;
}


int ServerModel::columnCount(const QModelIndex&) const
{
    return 5;
}


QVariant ServerModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole/* || role == Qt::ToolTipRole*/)
        return QString("Row %1 col %2").arg(index.row()).arg(index.column());
    else
        return QVariant();
}


QVariant ServerModel::headerData(int section, Qt::Orientation, int role) const
{
    static const char* h[] = {"First", "Second", "Third", "Fourth", "Fifth"};

    if (role == Qt::DisplayRole/* || role == Qt::ToolTipRole*/)
        return h[section];
    else
        return QVariant();
}
