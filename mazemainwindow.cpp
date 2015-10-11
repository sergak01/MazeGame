#include "mazemainwindow.h"
#include "ui_mazemainwindow.h"


MazeMainWindow::MazeMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MazeMainWindow)
{
    ui->setupUi(this);
    this->setGeometry(200, 100,530,600);
    this->setWindowTitle("Гра Лабіринт");
    winnerCount = 1;
    Iterator = 0;
    win = false;
    edit = false;

//tableTemp----------------------------
    for(int i = 0; i < 50; i++)
        tableTemp[i] = new MazePoint[50];
//-------------------------------------

//create Menu--------------------------
    mFile = new QMenu(tr("&Файл"), this);

    //New File-------------------------
    nFileM = new QAction(tr("&Новий файл"), this);
    nFileM->setShortcut(QKeySequence::New);
    mFile->addAction(nFileM);
    connect(nFileM, SIGNAL(triggered(bool)), this, SLOT(mNewFile()));
    //---------------------------------

    //Open File------------------------
    oFileM = new QAction(tr("&Відкрити файл"), this);
    oFileM->setShortcut(QKeySequence::Open);
    mFile->addAction(oFileM);
    connect(oFileM, SIGNAL(triggered(bool)), this, SLOT(mOpenFile()));
    //---------------------------------

    //Save File------------------------
    sFileM = new QAction(tr("&Зберегти файл"), this);
    sFileM->setShortcut(QKeySequence::Save);
    mFile->addAction(sFileM);
    connect(sFileM, SIGNAL(triggered(bool)), this, SLOT(mSaveFile()));
    //---------------------------------

    mFile->addSeparator();

    //Exit-----------------------------
    exitM = new QAction(tr("В&ихід"), this);
    exitM->setShortcut(QKeySequence::Close);
    mFile->addAction(exitM);
    connect(exitM, SIGNAL(triggered(bool)), this, SLOT(close()));
    //---------------------------------

    //About----------------------------
    About = new QMenu(tr("&Допомога"), this);
    aAbout = new QAction(tr("&Про програму"), this);
    aAbout->setShortcut(QKeySequence::HelpContents);
    About->addAction(aAbout);
    //---------------------------------

    ui->menuBar->addMenu(mFile);
    ui->menuBar->addMenu(About);
    ButtonStart = new QPushButton("Знайти шлях", this);
    ButtonStart->setGeometry(220, 540, 100, 35);
    connect(ButtonStart, SIGNAL(clicked(bool)), this, SLOT(startButtonClicked()));
//-------------------------------------

//create Maze--------------------------
    tableWidget = new MazePainter();
    tableWidget->setParent(this);
    tableWidget->setColumnCount(50);
    tableWidget->setRowCount(50);
    tableWidget->horizontalHeader()->setVisible(false);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setShowGrid(false);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setItemDelegate(new MazePainterBorder(tableWidget->getMaze()));
    for(int i = 0; i < 50; i++){
        tableWidget->setColumnWidth(i, 10);
        tableWidget->setRowHeight(i, 10);
    }
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setGeometry(10, 25, 510, 510);
    tableWidget->show();

    keyPressed_W = new QAction(tableWidget);
    keyPressed_W->setShortcut(Qt::Key_W);
    connect(keyPressed_W, SIGNAL(triggered(bool)), this, SLOT(keyPressedW()));
    tableWidget->addAction(keyPressed_W);

    keyPressed_S = new QAction(tableWidget);
    keyPressed_S->setShortcut(Qt::Key_S);
    connect(keyPressed_S, SIGNAL(triggered(bool)), this, SLOT(keyPressedS()));
    tableWidget->addAction(keyPressed_S);

    keyPressed_A = new QAction(tableWidget);
    keyPressed_A->setShortcut(Qt::Key_A);
    connect(keyPressed_A, SIGNAL(triggered(bool)), this, SLOT(keyPressedA()));
    tableWidget->addAction(keyPressed_A);

    keyPressed_D = new QAction(tableWidget);
    keyPressed_D->setShortcut(Qt::Key_D);
    connect(keyPressed_D, SIGNAL(triggered(bool)), this, SLOT(keyPressedD()));
    tableWidget->addAction(keyPressed_D);
//-------------------------------------

//    tableWidget->setSide(0, 1, 1, 0, 0, 0);
//    for(int i = 1; i < 49; i++)
//    //tableWidget->setSide(0, 0, 1, 1, 1, 0);
//    //tableWidget->setSide(0, 1, 1, 1, 2, 0);
//        tableWidget->setSide(1, 1, 0, 0, 0, i);
//    //tableWidget->setSide(1, 1, 0, 0, 0, 2);
//    //tableWidget->setSide(1, 1, 0, 0, 0, 3);
//    tableWidget->setSide(1, 0, 0, 1, 0, 49);
//    tableWidget->setSide(0, 0, 1, 1, 1, 49);
//    tableWidget->setSide(0, 1, 0, 1, 2, 49);
//    for(int i = 1; i < 49; i++)
//        tableWidget->setSide(1, 1, 0, 0, 2, i);
//    tableWidget->setSide(1, 0, 1, 0, 2, 0);
//    tableWidget->setSide(0, 0, 1, 1, 3, 0);
//    tableWidget->setSide(0, 0, 1, 0, 4, 0);
//    tableWidget->setSide(0, 1, 1, 1, 5, 0);
//    tableWidget->setSide(1, 1, 0, 0, 4, 1);
//    for(int i = 2; i < 20; i++)
//        tableWidget->setSide(1, 1, 0, 0, 4, i);
//    tableWidget->setSide(1, 1, 0, 1, 4, 19);
//    for(int i = 5; i < 13; i++)
//        tableWidget->setSide(0, 0, 1, 1, i, 7);
//    tableWidget->setSide(0, 1, 1, 1, 12, 7);
//    tableWidget->setSide(1, 0, 0, 0, 4, 7);
//    for(int i = 0; i < 50; i++){
//        MazePoint temp = tableWidget->getSide(0, i);
//        temp.pLeft = 1;
//        tableWidget->setSide(temp);
//        temp = tableWidget->getSide(i, 0);
//        temp.pTop = 1;
//        tableWidget->setSide(temp);
//        temp = tableWidget->getSide(49, i);
//        temp.pRight = 1;
//        tableWidget->setSide(temp);
//        temp = tableWidget->getSide(i, 49);
//        temp.pBottom = 1;
//        tableWidget->setSide(temp);
//    }

}

MazeMainWindow::~MazeMainWindow()
{
    delete ui;
}

void MazeMainWindow::MyWayBuilder(MazePoint **mP){
    MazePoint winPoint;
    MazePoint temp;
    winner_way[0].left = 0;
    winner_way[0].top = 0;
    winPoint.sLeft = tableWidget->columnCount() - 1;
    winPoint.sTop = tableWidget->rowCount() - 1;
    while(!win){
        if(mP[winner_way[winnerCount - 1].top][winner_way[winnerCount - 1].left].pRight == false){
            winner_way[winnerCount].left = winner_way[winnerCount - 1].left + 1;
            winner_way[winnerCount].top = winner_way[winnerCount - 1].top;
            temp = tableWidget->getSide(&winner_way[winnerCount - 1]);
            temp.pRight = true;
            tableWidget->setSide(temp);
            temp = tableWidget->getSide(&winner_way[winnerCount]);
            temp.pLeft = true;
            tableWidget->setSide(temp);
            winnerCount++;
        }
        else if(mP[winner_way[winnerCount - 1].top][winner_way[winnerCount - 1].left].pBottom == false){
            winner_way[winnerCount].left = winner_way[winnerCount - 1].left;
            winner_way[winnerCount].top = winner_way[winnerCount - 1].top + 1;
            temp = tableWidget->getSide(&winner_way[winnerCount - 1]);
            temp.pBottom = true;
            tableWidget->setSide(temp);
            temp = tableWidget->getSide(&winner_way[winnerCount]);
            temp.pTop = true;
            tableWidget->setSide(temp);
            winnerCount++;
        }
        else if(mP[winner_way[winnerCount - 1].top][winner_way[winnerCount - 1].left].pLeft == false){
            winner_way[winnerCount].left = winner_way[winnerCount - 1].left - 1;
            winner_way[winnerCount].top = winner_way[winnerCount - 1].top;
            temp = tableWidget->getSide(&winner_way[winnerCount - 1]);
            temp.pLeft = true;
            tableWidget->setSide(temp);
            temp = tableWidget->getSide(&winner_way[winnerCount]);
            temp.pRight = true;
            tableWidget->setSide(temp);
            winnerCount++;
        }
        else if(mP[winner_way[winnerCount - 1].top][winner_way[winnerCount - 1].left].pTop == false){
            winner_way[winnerCount].left = winner_way[winnerCount - 1].left;
            winner_way[winnerCount].top = winner_way[winnerCount - 1].top - 1;
            temp = tableWidget->getSide(&winner_way[winnerCount - 1]);
            temp.pTop = true;
            tableWidget->setSide(temp);
            temp = tableWidget->getSide(&winner_way[winnerCount]);
            temp.pBottom = true;
            tableWidget->setSide(temp);
            winnerCount++;
        }
        else{
            for(int i = winnerCount; i >= 0; i--){
                if(mP[winner_way[i].top][winner_way[i].left].pBottom != true ||
                        mP[winner_way[i].top][winner_way[i].left].pLeft != true ||
                        mP[winner_way[i].top][winner_way[i].left].pRight != true ||
                        mP[winner_way[i].top][winner_way[i].left].pTop != true){
                    winner_way[winnerCount].left = winner_way[i].left;
                    winner_way[winnerCount].top = winner_way[i].top;
                    winnerCount++;
                    break;
                }
                if(i == 0){
                    winner_way[winnerCount].left = 0;
                    winner_way[winnerCount].top = 0;
                    win = true;
                }
            }
        }
        if(winner_way[winnerCount - 1].left == winPoint.sLeft && winner_way[winnerCount - 1].top == winPoint.sTop)
            break;
    }

//-------------------------------------------------------------------
    WinWay point;
    finishCount = 0;
    for(int i = 0; i < winnerCount; i++){
        point = winner_way[i];
        for(int j = i + 1; j <= winnerCount - 1; j++){
            if(point.left == winner_way[j].left && point.top == winner_way[j].top){
                i = j;
                finish_way[finishCount] = winner_way[j];
                finishCount++;
            }
            else if(j == winnerCount - 1){
                finish_way[finishCount] = winner_way[i];
                finishCount++;
            }
        }
    }
    for(int i = 0; i < finishCount; i++){
        MazePoint mP;
        mP = tableWidget->getSide(&finish_way[i]);
        mP.pBottom = 0;
        mP.pLeft = 0;
        mP.pRight = 0;
        mP.pTop = 0;
        tableWidget->setSide(mP);
    }
//-------------------------------------------------------------------

}

void MazeMainWindow::PaintWay(WinWay *w){
    MazePoint **mPt;
    MazePoint **mP;
        mP = tableWidget->getMaze();
        mPt = tableTemp;
        QImage img;
        if(mP[w->top][w->left].pLeft != 1 ||
                mP[w->top][w->left].pRight != 1 ||
                mP[w->top][w->left].pTop != 1 ||
                mP[w->top][w->left].pBottom != 1){
            QTableWidgetItem *newItem = new QTableWidgetItem();
            tableWidget->setItem(mP[w->top][w->left].sTop,
                    mP[w->top][w->left].sLeft, newItem);
            if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoBotSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoLeftSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoRightSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoTopSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoBotLeftSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoRightBotSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoTopBotSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoRightLeftSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoTopLeftSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoTopRightSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoLeftBotRightSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoLeftTopRightSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoTopRightBotSideYellow.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoBotLeftTopSideYellow.png");
            else img.load("Side/NoAllSideYellow.png");
            tableWidget->item(mP[w->top][w->left].sTop,
                    mP[w->top][w->left].sLeft)->setBackground(QBrush(img));
        }
        else{
            QTableWidgetItem *newItem = new QTableWidgetItem();
            tableWidget->setItem(mP[w->top][w->left].sTop,
                    mP[w->top][w->left].sLeft, newItem);
            if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoBotSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoLeftSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoRightSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoTopSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoBotLeftSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoRightBotSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoTopBotSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoRightLeftSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoTopLeftSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoTopRightSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 1)
                img.load("Side/NoLeftBotRightSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 1 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoLeftTopRightSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 1 &&
                    mPt[w->top][w->left].pRight == 0 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoTopRightBotSideRed.png");
            else if(mPt[w->top][w->left].pBottom == 0 &&
                    mPt[w->top][w->left].pLeft == 0 &&
                    mPt[w->top][w->left].pRight == 1 &&
                    mPt[w->top][w->left].pTop == 0)
                img.load("Side/NoBotLeftTopSideRed.png");
            else img.load("Side/NoAllSideRed.png");
            tableWidget->item(mP[w->top][w->left].sTop,
                    mP[w->top][w->left].sLeft)->setBackground(QBrush(img));
        }
}

void MazeMainWindow::mNewFile(){
    edit = true;
    sFileM->setEnabled(true);
}

void MazeMainWindow::mOpenFile(){
    sFileM->setEnabled(false);
    QFile file;
    file.setFileName("labirint.maze");
    int point[10000];
    int counter = 0;
    editCount = 0;
    QByteArray bA;
    char ch;
    if(file.open(QIODevice::ReadOnly)){
        bA = file.readAll();
        for(int i = 0; i < bA.length(); i++){
            ch = bA[i];
            if(ch == '1'){
                point[counter] = 1;
                counter++;
            }
            else if(ch == '0'){
                point[counter] = 0;
                counter++;
            }
        }
        file.close();
        MazePoint **mP;
        counter = 0;
        mP = tableWidget->getMaze();
        for(int i = 0; i < 50; i++)
            for(int j = 0; j < 50; j++){
                mP[i][j].pLeft = point[counter];
                counter++;
                mP[i][j].pRight = point[counter];
                counter++;
                mP[i][j].pTop = point[counter];
                counter++;
                mP[i][j].pBottom = point[counter];
                counter++;
            }
    }
    tableWidget->setItemDelegate(new MazePainterBorder(tableWidget->getMaze()));
    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 50; j++){
            tableTemp[i][j].pBottom = tableWidget->getSide(j, i).pBottom;
            tableTemp[i][j].pLeft = tableWidget->getSide(j, i).pLeft;
            tableTemp[i][j].pRight = tableWidget->getSide(j, i).pRight;
            tableTemp[i][j].pTop = tableWidget->getSide(j, i).pTop;
            tableTemp[i][j].sLeft = tableWidget->getSide(j, i).sLeft;
            tableTemp[i][j].sTop = tableWidget->getSide(j, i).sTop;
        }
}

void MazeMainWindow::mSaveFile(){
    QFile file;
    file.setFileName("labirint.maze");
    if(file.exists()){
        file.setFileName(file.fileName() + "1.maze");
    }
    if(file.open(QIODevice::WriteOnly)){
        MazePoint **mP;
        mP = tableWidget->getMaze();
        QByteArray bA;
        for(int i = 0; i < 50; i++){
            for(int j = 0; j < 50; j++){
                QString str = "";
                if(mP[i][j].pLeft == true || mP[i][j].pLeft == 1)
                    str += QString::number(1) + " ";
                else str += QString::number(0) + " ";

                if(mP[i][j].pRight == true || mP[i][j].pRight == 1)
                    str += QString::number(1) + " ";
                else str += QString::number(0) + " ";

                if(mP[i][j].pTop == true || mP[i][j].pTop == 1)
                    str += QString::number(1) + " ";
                else str += QString::number(0) + " ";

                if(mP[i][j].pBottom == true || mP[i][j].pBottom == 1)
                    str += QString::number(1) + " ";
                else str += QString::number(0) + " ";
                bA.append(str);
            }
        }
        file.write(bA);
        file.close();
    }
}

void MazeMainWindow::startButtonClicked(){
    MyWayBuilder(tableWidget->getMaze());
    QTimer *timer = new QTimer(this);
    timer->setInterval(15);

    for(int i = 0; i < winnerCount; i++)
        timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerOut()));
}

WinWay MazeMainWindow::getSelectCell(){
    WinWay temp;
    temp.top = tableWidget->selectionModel()->currentIndex().row();
    temp.left = tableWidget->selectionModel()->currentIndex().column();
    return temp;
}

void MazeMainWindow::keyPressedW(){
    if(edit == true){
        MazePoint **mPoint = tableWidget->getMaze();
        WinWay cell;
        cell = getSelectCell();
        if(mPoint[cell.top][cell.left].pTop == 1){
            mPoint[cell.top][cell.left].pTop = 0;
            if(cell.top > 0)
                mPoint[cell.top - 1][cell.left].pBottom = 0;
        }
        else{
            mPoint[cell.top][cell.left].pTop = 1;
            if(cell.top > 0)
                mPoint[cell.top - 1][cell.left].pBottom = 1;
        }
        tableWidget->setForegroundRole(QPalette::Foreground);
    }
}

void MazeMainWindow::keyPressedS(){
    if(edit == true){
        MazePoint **mPoint = tableWidget->getMaze();
        WinWay cell;
        cell = getSelectCell();
        if(mPoint[cell.top][cell.left].pBottom == 1){
                mPoint[cell.top][cell.left].pBottom = 0;
                if(cell.top < tableWidget->rowCount())
                    mPoint[cell.top + 1][cell.left].pTop = 0;
            }
        else{
            mPoint[cell.top][cell.left].pBottom = 1;
            if(cell.top < tableWidget->rowCount())
                mPoint[cell.top + 1][cell.left].pTop = 1;
        }
        tableWidget->setForegroundRole(QPalette::Foreground);
    }
}

void MazeMainWindow::keyPressedA(){
    if(edit == true){
        MazePoint **mPoint = tableWidget->getMaze();
        WinWay cell;
        cell = getSelectCell();
        if(mPoint[cell.top][cell.left].pLeft == 1){
            mPoint[cell.top][cell.left].pLeft = 0;
            if(cell.left > 0)
                mPoint[cell.top][cell.left - 1].pRight = 0;
        }
        else{
            mPoint[cell.top][cell.left].pLeft = 1;
            if(cell.left > 0)
                mPoint[cell.top][cell.left - 1].pRight = 1;
        }
        tableWidget->setForegroundRole(QPalette::Foreground);
    }
}

void MazeMainWindow::keyPressedD(){
    if(edit == true){
        MazePoint **mPoint = tableWidget->getMaze();
        WinWay cell;
        cell = getSelectCell();
        if(mPoint[cell.top][cell.left].pRight == 1){
            mPoint[cell.top][cell.left].pRight = 0;
            if(cell.left < tableWidget->columnCount())
                mPoint[cell.top][cell.left + 1].pLeft = 0;
        }
        else{
            mPoint[cell.top][cell.left].pRight = 1;
            if(cell.left < tableWidget->columnCount())
                mPoint[cell.top][cell.left + 1].pLeft = 1;
        }
        tableWidget->setForegroundRole(QPalette::Foreground);
    }
}

void MazeMainWindow::timerOut(){
    PaintWay(&winner_way[Iterator]);
    Iterator++;
}
