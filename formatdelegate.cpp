#include "formatdelegate.h"

#include <QDebug>

FormatDelegate::FormatDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void FormatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    //painter->drawText(option.rect.bottomLeft(), index.model()->data(index).toString());
    QStyledItemDelegate::paint(painter, option, index);
    qDebug() << "painting" << index.model()->data(index).toString();
}

QSize FormatDelegate::sizeHint(const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
  return QSize(100,100);
}
