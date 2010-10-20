#ifndef FORMATDELEGATE_H
#define FORMATDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class FormatDelegate : public QStyledItemDelegate
{

public:
    FormatDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;

};

#endif // FORMATDELEGATE_H
