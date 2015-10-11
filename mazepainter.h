#ifndef MAZEPAINTER_H
#define MAZEPAINTER_H

#include <QTableWidget>

//Struct for side of one point
struct MazePoint{
    bool pLeft;
    bool pRight;
    bool pTop;
    bool pBottom;
    int sLeft;
    int sTop;
};
//---------------------------

//Struct for winner way------
struct WinWay{
    int left;
    int top;
};
//---------------------------

class MazePainter : public QTableWidget
{
private:
    MazePoint *mPoint[50];
public:
    MazePainter();
    ~MazePainter();
    void setSide(bool Left, bool Right, bool Top, bool Bottom, int sLeft, int sTop);
    void setSide(MazePoint mP);
    MazePoint getSide(int sLeft, int sTop);
    MazePoint **getMaze();
    MazePoint getSide(WinWay *ww);
};

#endif // MAZEPAINTER_H
