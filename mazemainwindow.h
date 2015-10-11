#ifndef MAZEMAINWINDOW_H
#define MAZEMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFile>
#include <QTimer>
#include "mazepainter.h"
#include "mazepainterborder.h"

namespace Ui {
class MazeMainWindow;
}

class MazeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MazeMainWindow(QWidget *parent = 0);
    ~MazeMainWindow();
    void MyWayBuilder(MazePoint **mP);
    void PaintWay(WinWay *w);
    WinWay getSelectCell();

private:
    Ui::MazeMainWindow *ui;
    WinWay winner_way[5000];
    WinWay finish_way[5000];
    unsigned int finishCount;
    MazePainter *tableWidget;
    MazePoint *tableTemp[50];
    unsigned int winnerCount;
    bool win;
    bool edit;
    int editCount;
    int Iterator;

//Menu and Interface---------
    QMenu *mFile;
    QAction *nFileM;
    QAction *oFileM;
    QAction *sFileM;
    QAction *exitM;
    QMenu *About;
    QAction *aAbout;
    //End Menu

    QPushButton *ButtonStart;
    QAction *keyPressed_W;
    QAction *keyPressed_S;
    QAction *keyPressed_A;
    QAction *keyPressed_D;
//---------------------------

public slots:
    void mNewFile();
    void mOpenFile();
    void mSaveFile();
    void startButtonClicked();
    void keyPressedW();
    void keyPressedS();
    void keyPressedA();
    void keyPressedD();
    void timerOut();

};

#endif // MAZEMAINWINDOW_H
