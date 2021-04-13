#include "othello.h"
#include "ui_othello.h"
#include <Qpainter>
#include <QPixmap>
#include "QCursor"
#include <iostream>
#include<QDebug>
#include "QMouseEvent"
#include <string>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <queue>
#include <stack>
#include<QSize>
#include <conio.h>
using namespace std;
bool mousedown = false;
int mousex;
int mousey;
Board * mainBoard;
othello::othello(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::othello)
{
    ui->setupUi(this);
    init();
    mainBoard=new Board();
    resetBoard(mainBoard);
    turn="a";
    playera=Blackchess;
    playerb=Whitechess;
    background.load("C:/Users/kentl/Documents/build-Othello-Desktop_Qt_5_9_6_MinGW_32bit-Debug/debug/images/1.jpg");
    black.load("G:/noir.png");
    white.load("G:/blanc.png");
    hintblack.load("G:/hintblack.png");
    hintwhite.load("G:/hintwhite.png");
    background=background.scaled(QSize(400,400), Qt::KeepAspectRatio);
    black=black.scaled(QSize(50,50),Qt::KeepAspectRatio);
    white=white.scaled(QSize(50,50),Qt::KeepAspectRatio);
    hintblack=hintblack.scaled(QSize(50,50),Qt::KeepAspectRatio);
    hintwhite=hintwhite.scaled(QSize(50,50),Qt::KeepAspectRatio);
}

othello::~othello()
{
    delete ui;
}
void othello::init(){
    struct posnode originpos;
    originpos.x=originpos.y=8;

}
void othello::mousePressEvent(QMouseEvent *e){
    mousex=e->x()/50;
    mousey=e->y()/50;
    if(turn.compare("a")==0&&isGameOver(mainBoard)!=true&&!gameOver){
        if(makeMove(mainBoard,playera,mousex,mousey)==true){
            makeMove(mainBoard,playera,mousex,mousey);
            Last.x=mousex;
            Last.y=mousey;
            if(getMove(mainBoard,playerb).size()!=0){
                turn="b";
            }
        }
        else{
            cout<<"Reinput"<<endl;
        }
    }else{
        if(makeMove(mainBoard,playerb,mousex,mousey)==true){
            makeMove(mainBoard,playera,mousex,mousey);
            Last.x=mousex;
            Last.y=mousey;
            if(getMove(mainBoard,playera).size()!=0){
                turn="a";
            }
        }
        else{
            cout<<"Reinput"<<endl;
        }
    }
    repaint();
}
void othello::paintEvent(QPaintEvent *event){
    this->resize(600,400);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);
    painter.drawPixmap(0,0,400,400,background);
    int c;
    if(turn=="b"){
        c=Whitechess;
    }
    else{
        c=Blackchess;
    }
    int potential[8][8];
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            potential[i][j]=0;
        }
    }
   vector<posi> nodes =getMove(mainBoard,c);
   for(int i=0;i<nodes.size();i++){
       int x=nodes[i].x;
       int y=nodes[i].y;
       potential[x][y]=c;
   }
   for(int i=0;i<8;i++){
       for(int j=0;j<8;j++){
           if(mainBoard->get(i,j)==Whitechess){
               painter.drawPixmap(0+50*i,0+50*j,50,50,white);
           }
           else if(mainBoard->get(i,j)==Blackchess){
               painter.drawPixmap(0+50*i,0+50*j,50,50,black);
           }
           if(potential[i][j]==Blackchess){
               painter.drawPixmap(0+50*i,0+50*j,50,50,hintblack);
           }
           if(potential[i][j]==Whitechess){
               painter.drawPixmap(0+50*i,0+50*j,50,50,hintwhite);
           }
       }
   }
}
bool othello::makeMove(Board *mainboard, int playerTile, int col, int row){
    vector<posi> tilesToFlip = isValid(mainboard, playerTile, col, row);

        if (tilesToFlip.size()==0) {
            return false;
        }

        mainboard->set(col, row, playerTile);

        while (tilesToFlip.size()!=0) {
            posi tilepos = tilesToFlip.back();
            tilesToFlip.pop_back();
            mainboard->set(tilepos.x, tilepos.y, playerTile);
        }
        repaint();
        return true;
}
vector<posi> othello::isValid(Board *board, int tile, int col, int row){
    vector<posi> tilesToFlip;
        if (isOnBoard(col, row) == false || board->get(col, row) != 0) {
            return tilesToFlip;
        }
        int othertile;
        board->set(col, row, tile);

        if (tile == Blackchess) {
            othertile = Whitechess;
        }
        else {
            othertile = Blackchess;
        }


        for (int i = 0; i < 8; i++) {
            int x = col;
            int y = row;
            int xdirection = Direction[i][0];
            int ydirection = Direction[i][1];
            x += xdirection;
            y += ydirection;
            if (isOnBoard(x, y) && board->get(x, y) == othertile) {
                x += xdirection;
                y += ydirection;
                if (isOnBoard(x, y) == false) {
                    continue;
                }

                while (board->get(x, y) == othertile) {
                    x += xdirection;
                    y += ydirection;
                    if (isOnBoard(x, y) == false) {
                        break;
                    }
                }

                if (isOnBoard(x, y) == false) {
                    continue;
                }

                if (board->get(x, y) == tile) {
                    while (true) {
                        x -= xdirection;
                        y -= ydirection;

                        if (x == col && y == row) {
                            break;
                        }
                        tilesToFlip.push_back(posi(x, y));
                    }
                }
            }
        }
        board->set(col, row, 0);
        return tilesToFlip;
}
vector<posi> othello::getMove(Board *board, int tile){
    vector<posi> validMoves;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++){
                 if (isValid(board, tile, i, j).size() != 0) {
                    validMoves.push_back(posi(i, j));
                 }
            }
        }
        return validMoves;
}
bool othello::isOnBoard(int x, int y){
    return x>=0&&x<=7&&y>=0&&y<=7;
}
bool othello::isOnCorner(int x,int y){
    return (x==0&&y==0)||(x==7&&y==0)||(x==0&&y==7);
}
bool othello::isGameOver(Board* board) {
    int black = 0;
    int white = 0;
    int flag = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->get(i, j) == Blackchess) {
                black++;
            }
            else if (board->get(i, j) == Whitechess) {
                white++;
            }
            else {
                flag++;
            }
        }
    }

    if (black == 0 || white == 0) {
        return true;
    }

    if (flag != 0) {
        return false;
    }

    return true;
}
void othello::resetBoard(Board *board){
    board->init();
    board->set(3,3,Whitechess);
    board->set(3,4,Blackchess);
    board->set(4,3,Blackchess);
    board->set(4,4,Whitechess);
}
void othello::on_pushButton_clicked()
{
    isGameStart=true;
    resetBoard(mainBoard);
    turn="a";
}
