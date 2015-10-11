#include "mazepainterborder.h"

MazePainterBorder::MazePainterBorder()
{
    check = false;
}

MazePainterBorder::MazePainterBorder(MazePoint **mP){
    mPoint = mP;
    check = true;
}

void MazePainterBorder::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    const QRect rect(option.rect);
    painter->setPen(Qt::black);
    if(check == false){
        if(index.row() == 0)
            painter->drawLine(rect.topLeft(), rect.topRight());
        painter->drawLine( rect.bottomLeft(), rect.bottomRight() );
        if (index.column() == 0)
            painter->drawLine( rect.topLeft(), rect.bottomLeft() );
        painter->drawLine(rect.topRight(), rect.bottomRight());
    }
    else{
        MazePoint temp;
        temp.pBottom = mPoint[index.row()][index.column()].pBottom;
        temp.pTop = mPoint[index.row()][index.column()].pTop;
        temp.pLeft = mPoint[index.row()][index.column()].pLeft;
        temp.pRight = mPoint[index.row()][index.column()].pRight;

        if(temp.pTop == true)
            painter->drawLine(rect.topLeft(), rect.topRight());
        if(temp.pLeft == true)
            painter->drawLine(rect.topLeft(), rect.bottomLeft());
        if(temp.pRight == true)
            painter->drawLine(rect.topRight(), rect.bottomRight());
        if(temp.pBottom == true)
           painter->drawLine(rect.bottomLeft(), rect.bottomRight());
    }
    QStyledItemDelegate::paint( painter, option, index );
}


MazePainterBorder::~MazePainterBorder(){

}
