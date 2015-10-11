#include "mazepainter.h"

MazePainter::MazePainter()
{
    for(int i = 0; i < 50; i++)
        mPoint[i] = new MazePoint[50];
    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 50; j++){
            mPoint[i][j].pBottom = 1;
            mPoint[i][j].pLeft = 1;
            mPoint[i][j].pRight = 1;
            mPoint[i][j].pTop = 1;
            mPoint[i][j].sLeft = j;
            mPoint[i][j].sTop = i;
        }
}

MazePainter::~MazePainter()
{

}

void MazePainter::setSide(bool Left, bool Right, bool Top, bool Bottom, int sLeft, int sTop){
    mPoint[sTop][sLeft].pLeft = Left;
    mPoint[sTop][sLeft].pRight = Right;
    mPoint[sTop][sLeft].pTop = Top;
    mPoint[sTop][sLeft].pBottom = Bottom;
    mPoint[sTop][sLeft].sLeft = sLeft;
    mPoint[sTop][sLeft].sTop = sTop;
}

void MazePainter::setSide(MazePoint mP){
    mPoint[mP.sTop][mP.sLeft].pLeft = mP.pLeft;
    mPoint[mP.sTop][mP.sLeft].pRight = mP.pRight;
    mPoint[mP.sTop][mP.sLeft].pTop = mP.pTop;
    mPoint[mP.sTop][mP.sLeft].pBottom = mP.pBottom;
    mPoint[mP.sTop][mP.sLeft].sLeft = mP.sLeft;
    mPoint[mP.sTop][mP.sLeft].sTop = mP.sTop;
}

MazePoint MazePainter::getSide(int sLeft, int sTop){
    MazePoint temp;
    if(sLeft > 50) sLeft = 49;
    if(sTop > 50) sTop = 49;
    if(sLeft < 0 || sTop < 0){
        temp.pBottom = 0;
        temp.pLeft = 0;
        temp.pRight = 0;
        temp.pTop = 0;
        temp.sLeft = 0;
        temp.sTop = 0;
    }
    else{
        temp.pLeft = mPoint[sTop][sLeft].pLeft;
        temp.pRight = mPoint[sTop][sLeft].pRight;
        temp.pTop = mPoint[sTop][sLeft].pTop;
        temp.pBottom = mPoint[sTop][sLeft].pBottom;
        temp.sLeft = mPoint[sTop][sLeft].sLeft;
        temp.sTop = mPoint[sTop][sLeft].sTop;
    }
    return temp;
}

MazePoint MazePainter::getSide(WinWay *ww){
    MazePoint temp;
    if(ww->left < 0 || ww->top < 0){
        temp.pBottom = 0;
        temp.pLeft = 0;
        temp.pRight = 0;
        temp.pTop = 0;
        temp.sLeft = 0;
        temp.sTop = 0;
        return temp;
    }
    else{
        temp.pLeft = mPoint[ww->top][ww->left].pLeft;
        temp.pRight = mPoint[ww->top][ww->left].pRight;
        temp.pTop = mPoint[ww->top][ww->left].pTop;
        temp.pBottom = mPoint[ww->top][ww->left].pBottom;
        temp.sLeft = mPoint[ww->top][ww->left].sLeft;
        temp.sTop = mPoint[ww->top][ww->left].sTop;
        return temp;
    }
}

MazePoint **MazePainter::getMaze(){
    return mPoint;
}
