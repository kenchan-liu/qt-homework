#ifndef OTHELLO_H
#define OTHELLO_H

#include <QMainWindow>
#include<stdio.h>
#include<string>
#include<iostream>
#include<vector>
#include"QMutex"
#include"QButtonGroup"
#include<QPixmap>
#include<QPaintEvent>
using namespace std;
#define Whitechess  1
#define Blackchess  2
typedef struct posnode {
    int x;
    int y;
    posnode(int x, int y) {
        this->x = x;
        this->y = y;
    }
    posnode() {
        x = y = -1;
    }
}posi;
class Board {
    int ch[8][8];

public:
    int get(int i, int j) {
        return ch[i][j];
    }

    void set(int i, int j, int val) {
        ch[i][j] = val;
    }

    void init() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                ch[i][j] = 0;
            }
        }
    }
};
namespace Ui {
class othello;
}

class othello : public QMainWindow
{
    Q_OBJECT
    bool gameOver = false;
    int playera, playerb;
    int playert,computert;
    QMutex mutex;
    string turn;
    posi Last;
    int Direction[8][2] = {
        {0,1},{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{-1,1}
    };
    QButtonGroup *btnGroup;  
    QPixmap background,white,black,hintwhite,hintblack;
public:
    explicit othello(QWidget *parent = 0);
    bool isGameStart = false;
    void DrawBoard(int i);
    void init();
    Board* getNewBoard();
    Board* getBoardCopy(Board* board);
    void resetBoard(Board* board);
    bool makeMove(Board* mainboard, int playerTile, int col, int row);
    vector<posi> isValidMove(Board* board, int tile, int xstart, int ystart);
    vector<posi> getValidMove(Board* board, int tile);
    bool isOnBoard(int x, int y);
    bool isOnCorner(int x,int y);
    void printBoard(Board* board);
    bool isGameOver(Board* board);
    void start();
    ~othello();

private:
    Ui::othello *ui;
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e); 
private slots:
    void on_pushButton_clicked();
};

#endif // OTHELLO_H
