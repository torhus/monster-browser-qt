#ifndef SERVERMODEL_H
#define SERVERMODEL_H

#include "masterlist.h"
#include <memory>
#include <QAbstractItemModel>


class ServerModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ServerModel(QObject* parent);
    virtual ~ServerModel();
    QModelIndex index(int row, int column,
                      const QModelIndex& parent = QModelIndex())
                      const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const
                                                                      override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    MasterList& master() const { return *master_; }

private:
    std::unique_ptr<MasterList> master_;
};

#endif // SERVERMODEL_H
