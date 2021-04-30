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
#include<QMessageBox>
#include<math.h>
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
    mode=1;
    mainBoard=new Board();
    resetBoard(mainBoard);
    turn="a";
    playera=Blackchess;
    playerb=Whitechess;
    playert=Blackchess;
    computert=Whitechess;
    nom=true;
    QString a;
    a= ui->lineEdit->text();
    hard=a.toInt();
    isGameStart=false;
    groupButton1=new QButtonGroup(this);
    groupButton1->addButton(ui->aim,0);
    groupButton1->addButton(ui->hmm,1);
    ui->hmm->setChecked(true); //默认human_mode
    connect(ui->pushButton, SIGNAL(clicked()),this,SLOT(ClickButton()));
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
void othello::on_pushButton_clicked(){
    if(isGameStart==false){
        QMessageBox msgBox;
        msgBox.setText("<a href = https://kenchan-liu.github.io/ >规则</a>");
        msgBox.exec();
        ui->pushButton->setText("Reset");
        turn="a";
        switch(groupButton1->checkedId())
        {
        case 0:
            mode=-1;
            break;
        case 1:
            mode=1;
            break;
        }
        isGameStart=true;
        resetBoard(mainBoard);
        repaint();
    }
    else{
        resetBoard(mainBoard);
        turn="a";
        isGameStart=false;
        repaint();
        ui->pushButton->setText("Start");
    }
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
    if(isGameStart){
    if(mode==1){
        mousex=e->x()/50;
        mousey=e->y()/50;
        if(turn.compare("a")==0&&isGameOver(mainBoard)!=true&&!gameOver){
            if(makeMove(mainBoard,playera,mousex,mousey)==true){
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
        ui->label_2->setText("black:"+QString::number(report(mainBoard,Blackchess)));
        ui->label_3->setText("white:"+QString::number(report(mainBoard,Whitechess)));
        repaint();
    }
    else{
        mousex=e->x()/50;
        mousey=e->y()/50;
        if(turn.compare("a")==0&&isGameOver(mainBoard)!=true&&!gameOver){
            if(makeMove(mainBoard,playert,mousex,mousey)==true){
                makeMove(mainBoard,playert,mousex,mousey);
                Last.x=mousex;
                Last.y=mousey;
                if(getMove(mainBoard,computert).size()!=0){
                    turn="b";
                }
            }
            repaint();
        }
        posi p;
        p=min(mainBoard,3,-9999,9999,Whitechess,hard);
        if(makeMove(mainBoard,computert,p.x,p.y)==true){
            if(getMove(mainBoard,playert).size()!=0){
                turn="a";
            }
        }
        ui->label_2->setText("black:"+QString::number(report(mainBoard,Blackchess)));
        ui->label_3->setText("white:"+QString::number(report(mainBoard,Whitechess)));
        repaint();
    }
    }
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
    if(isGameOver(mainBoard)&&nom){
        QMessageBox msgBox;
        if(report(mainBoard,Whitechess)>report(mainBoard,Blackchess))
            msgBox.setText("white win.");
        else
            msgBox.setText("black win.");
        msgBox.exec();
        nom=false;
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
int othello::report(Board *b,int t){
    int black=0,white=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if (b->get(i, j) == Blackchess) {
                black++;
            }
            else if (b->get(i, j) == Whitechess) {
                white++;
            }
        }
    }
    if(t==Whitechess){
        return white;
    }
    else
        return black;
}
void othello::resetBoard(Board *board){
    board->init();
    board->set(3,3,Whitechess);
    board->set(3,4,Blackchess);
    board->set(4,3,Blackchess);
    board->set(4,4,Whitechess);
}
posi othello::max(Board *mb, int depth, int alpha, int beta, int tile,int hard){
    int best = -10000;
    Board *nm=new Board();
    posi move ;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            nm->set(i,j,mb->get(i,j));
        }
    }
    vector<posi> gm=getMove(mb,tile);
    if(depth==0){
        for(int i=0;i<getMove(mb,tile).size();i++){
            nm->set(gm[i].x,gm[i].y,tile);
            if(evaluate(nm,hard)>best){
                best=evaluate(nm,hard);move=gm[i];
            }
            nm->set(gm[i].x,gm[i].y,0);
        }
        return move;
    }
    if(gm.size()==0){
        return move;
    }
    for (int i = 0; i < getMove(mb,tile).size(); i++) {
        alpha = best>alpha?best:alpha;
        if(alpha >= beta){
            break;
        }
        nm->set(gm[i].x,gm[i].y,tile);
        posi next;
        next=min(nm, depth - 1,alpha, beta, -tile, hard);
        nm->set(next.x,next.y,-tile);
        int value = evaluate(nm,hard);
        if (value < best) {
          best = value;
          move = gm[i];
        }
        nm->set(next.x,next.y,0);
        nm->set(gm[i].x, gm[i].y,0);
      }
      return move;
}
posi othello::min(Board *mb, int depth, int alpha, int beta, int tile,int hard){
    int best = 10000;
    Board *nm=new Board();
    posi move ;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            nm->set(i,j,mb->get(i,j));
        }
    }
    vector<posi> gm=getMove(mb,tile);
    if(depth==0){
        for(int i=0;i<getMove(mb,tile).size();i++){
            nm->set(gm[i].x,gm[i].y,tile);
            if(evaluate(nm,hard)<best){
                best=evaluate(nm,hard);move=gm[i];
            }
            nm->set(gm[i].x,gm[i].y,0);
        }
        return move;
    }
    for (int i = 0; i < getMove(mb,tile).size(); i++) {
        beta = best<beta?best:beta;
        if(alpha >= beta){
            break;
        }
        posi next;
        next=max(nm, depth - 1,alpha, beta, -tile, hard);
        nm->set(gm[i].x,gm[i].y,tile);
        nm->set(next.x,next.y,-tile);
        int value = evaluate(nm,hard);
        if (value < best) {
          best = value;
          move = gm[i];
        }
        nm->set(next.x,next.y,0);
        nm->set(gm[i].x, gm[i].y,0);
      }
      return move;
}
int othello::evaluate(Board *board, int hard) {
    int whiteEvaluate = 0;
    int blackEvaluate = 0;
    vector<posi>b,w;
    int sw,sb;
    int weight[5] = { 2, 4, 6, 10, 15 };
    switch (hard) {
    case 1:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (board->get(i,j) == Whitechess) {
            whiteEvaluate += 1;
          } else if (board->get(i,j) == Blackchess) {
            blackEvaluate += 1;
          }
        }
      }
      break;
    case 2:
    case 3:
    case 4:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if ((i == 0 || i == 7) && (j == 0 || j == 7)) {
            if (board->get(i,j) == Whitechess) {
              whiteEvaluate += 5;
            } else if (board->get(i,j) == Blackchess) {
              blackEvaluate += 5;
            }
          } else if (i == 0 || i == 7 || j == 0 || j == 7) {
            if (board->get(i,j) == Whitechess) {
              whiteEvaluate += 2;
            } else if (board->get(i,j) == Blackchess) {
              blackEvaluate += 2;
            }
          } else {
            if (board->get(i,j) == Whitechess) {
              whiteEvaluate += 1;
            } else if (board->get(i,j) == Blackchess) {
              blackEvaluate += 1;
            }
          }
        }
      }
      break;
    case 5:
    case 6:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if ((i == 0 || i == 7) && (j == 0 || j == 7)) {
            if (board->get(i,j) == Whitechess) {
              whiteEvaluate += 5;
            } else if (board->get(i,j) == Blackchess) {
              blackEvaluate += 5;
            }
          } else if (i == 0 || i == 7 || j == 0 || j == 7) {
            if (board->get(i,j) == Whitechess) {
              whiteEvaluate += 2;
            } else if (board->get(i,j) == Blackchess) {
              blackEvaluate += 2;
            }
          } else {
            if (board->get(i,j) == Whitechess) {
              whiteEvaluate += 1;
            } else if (board->get(i,j) == Blackchess) {
              blackEvaluate += 1;
            }
          }
        }
      }
      b=getMove(board,Blackchess);
      w=getMove(board,Whitechess);
      blackEvaluate = blackEvaluate * 2 + b.size();
      whiteEvaluate = whiteEvaluate * 2 + w.size();
      break;
    case 7:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (board->get(i,j) == Whitechess) {
            whiteEvaluate = whiteEvaluate + weight[getStability(board,posi(i, j))];
          } else if (board->get(i,j) == Blackchess) {
            blackEvaluate = blackEvaluate + weight[getStability(board, posi(i, j))];
          }
        }
      }
      b=getMove(board,Blackchess);
      w=getMove(board, Whitechess);
      sb=b.size();
      sw=w.size();
      blackEvaluate += sb;
      whiteEvaluate += sw;
      break;
    }
    return blackEvaluate - whiteEvaluate;
}
int othello::getStability(Board *b, posi p) {
    int chessColor = b->get(p.x,p.y);
    int drow[4][2]={ { 0, 0 }, { -1, 1 }, { -1, 1 }, { 1, -1 } }, dcol[4][2]={ { -1, 1 }, { 0, 0 }, { -1, 1 }, { -1, 1 } };
    int row[2],col[2];
    int degree = 0;
    for (int k = 0; k < 4; k++) {
        row[0] = row[1] = p.x;
        col[0] = col[1] = p.y;
        for (int i = 0; i < 2; i++) {
          while (isOnBoard(row[i] + drow[k][i], col[i] + dcol[k][i])
              && b->get(row[i] + drow[k][i],col[i] + dcol[k][i]) == chessColor) {
            row[i] += drow[k][i];
            col[i] += dcol[k][i];
          }
        }
        if (!isOnBoard(row[0] + drow[k][0], col[0] + dcol[k][0])
            || !isOnBoard(row[1] + drow[k][1], col[1] + dcol[k][1])) {
          degree += 1;
        } else if (b->get(row[0] + drow[k][0],col[0] + dcol[k][0]) == (-chessColor)
            && b->get(row[1] + drow[k][1],col[1] + dcol[k][1]) == (-chessColor)) {
          degree += 1;
        }
      }
    return degree;
}
