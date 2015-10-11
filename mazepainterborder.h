#ifndef MAZEPAINTERBORDER_H
#define MAZEPAINTERBORDER_H

#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QPainter>
#include "mazepainter.h"


class MazePainterBorder : public QStyledItemDelegate
{
public:
    MazePainterBorder();
    ~MazePainterBorder();
    MazePainterBorder(MazePoint **mP);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    MazePoint **mPoint;
    bool check;
};

#endif // MAZEPAINTERBORDER_H
