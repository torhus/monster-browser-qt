#include "serverview.h"
#include "colorednames.h"
#include "servermodel.h"
#include <array>
using namespace std;
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
            //QString text(index.model()->data(index).toString());
            QString rawName(
                      "^9gg.^4ill^7wie^1ckz^9.net^6 { ^5le frag courtois^6 }");
            QString name(stripColorCodes(rawName));
            QString subString;

            painter->save();
            /*if (option.state & QStyle::State_Selected)
                painter->fillRect(option.rect, option.palette.highlight());*/

            for (const auto& range: parseColors(rawName, true)) {
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
    setItemDelegateForColumn(1, new ServerItemDelegate(this));
    setModel(new ServerModel(this));
    setColumnWidth(1, 250);
}


ServerView::~ServerView()
{

}
