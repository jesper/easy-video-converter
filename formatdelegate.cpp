#include "formatdelegate.h"

#include <QDebug>

FormatDelegate::FormatDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void FormatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    if (option.state & QStyle::State_MouseOver)
        painter->fillRect(option.rect, Qt::lightGray);

    painter->drawText(0, option.rect.center().y(), index.model()->data(index).toString());
}

QSize FormatDelegate::sizeHint(const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
  return QSize(100,100);
}
