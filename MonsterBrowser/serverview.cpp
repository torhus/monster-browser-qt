#include "serverview.h"
#include "colorednames.h"
#include "servermodel.h"
#include <array>
using namespace std;
#include <QHeaderView>
#include <QPainter>
#include <QStyledItemDelegate>


// Implements custom painting for player names.
class ServerItemDelegate : public QStyledItemDelegate
{
    //Q_OBJECT
public:
    ServerItemDelegate(QObject* parent) : QStyledItemDelegate(parent) { }

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const
    {
        if (0 && option.state & QStyle::State_Selected) {
            // Use default rendering to make it more readable.
            QStyledItemDelegate::paint(painter, option, index);
        }
        else {
            QRect rect(option.rect);
            // Not sure what the correct way to get proper indentation is.
            rect.setLeft(rect.left() + 3);
            const ServerModel* model =
                               dynamic_cast<const ServerModel*>(index.model());
            ServerData& sd = model->master()[index.row()];
            QString& name = sd.server[ServerColumn::NAME];
            QString subString;

            painter->save();
            /*if (option.state & QStyle::State_Selected)
                painter->fillRect(option.rect, option.palette.highlight());*/

            for (const auto& range: parseColors(sd.rawName, true)) {
                subString.setRawData(&name.constData()[range.start],
                                     range.end - range.start + 1);
                painter->setPen(range.color);
                painter->drawText(rect, Qt::AlignVCenter, subString);
                rect.setLeft(rect.left() +
                             painter->fontMetrics().width(subString));
            }
            painter->restore();
        }
    }

};


ServerView::ServerView(QWidget* parent)
    : QTreeView(parent)
{
    setRootIsDecorated(false);
    setUniformRowHeights(true);
    setAlternatingRowColors(true);
    setSelectionMode(ExtendedSelection);
    setAllColumnsShowFocus(true);
    setSortingEnabled(true);
    setItemDelegateForColumn(1, new ServerItemDelegate(this));
    header()->setSectionsMovable(false);
    header()->setSortIndicator(ServerColumn::NAME, Qt::AscendingOrder);
}


ServerView::~ServerView()
{

}


void ServerView::setModel(QAbstractItemModel* model)
{
    static bool firstTime = true;

    QTreeView::setModel(model);

    if (auto m = dynamic_cast<ServerModel*>(model)) {
        serverModel_ = m;
    }
    else {
        // Something is very wrong if we get here.
        Q_ASSERT(m);
        serverModel_ = nullptr;
    }

    if (firstTime) {
        // Temporary solution.
        firstTime = false;
        int widths[8] = {27, 250, 21, 32, 50, 40, 90, 130};
        for (int i = 0; i < 8; i++) {
            setColumnWidth(i, widths[i]);
        }
    }
}


/**
 * Convenience method for getting the model without having to downcast from
 * QAbstractItemModel.
 */
ServerModel* ServerView::serverModel() const
{
    return serverModel_;
}
