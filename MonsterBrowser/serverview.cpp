#include "serverview.h"
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
        if (option.state & QStyle::State_Selected) {
            // Use default rendering to make it more readable.
            QStyledItemDelegate::paint(painter, option, index);
        }
        else {
            QRect rect(option.rect);
            // Not sure what the correct way to get proper indentation is.
            rect.setLeft(rect.left() + 3);
            QString text(index.model()->data(index).toString());
            QString subString;
            static array<QColor, 5> colors({Qt::red, Qt::blue, Qt::darkGreen,
                                            Qt::darkYellow, Qt::darkBlue});

            painter->save();
            /*if (option.state & QStyle::State_Selected)
                painter->fillRect(option.rect, option.palette.highlight());*/

            for (int i = 0; i < text.size(); i++) {
                subString.setRawData(&text.constData()[i], 1);
                painter->setPen(colors[i % colors.size()]);
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
}


ServerView::~ServerView()
{

}
