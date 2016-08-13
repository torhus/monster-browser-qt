#include "servermodel.h"
using namespace std;


const int NUM_COLUMNS = 8;


ServerModel::ServerModel(QObject* parent) : QAbstractItemModel(parent)
{
    master_ = make_shared<MasterList>();
    master_->load("68");
}


ServerModel:: ~ServerModel()
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
    return master_->size();
}


int ServerModel::columnCount(const QModelIndex&) const
{
    return NUM_COLUMNS;
}


QVariant ServerModel::data(const QModelIndex& index, int role) const
{
#if 0
    if (role == Qt::DisplayRole/* || role == Qt::ToolTipRole*/)
        return QString("Row %1 col %2").arg(index.row()).arg(index.column());
    else
        return QVariant();
#else
    if (role == Qt::DisplayRole/* || role == Qt::ToolTipRole*/)
        return master_->at(index.row()).server[index.column()];
    else
        return QVariant();
#endif
}


QVariant ServerModel::headerData(int section, Qt::Orientation, int role) const
{
    static const char* h[NUM_COLUMNS] = {"", "Name", "Passworded", "Ping",
                                      "Players", "Gametype", "Map", "Address"};

    if (role == Qt::DisplayRole/* || role == Qt::ToolTipRole*/)
        return h[section];
    else
        return QVariant();
}


void ServerModel::sort(int column, Qt::SortOrder order)
{
    emit layoutAboutToBeChanged();
    stable_sort(master_->begin(), master_->end(),
                ServerLessThan(column, order == Qt::DescendingOrder));
    emit layoutChanged();
}
