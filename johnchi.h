#ifndef JOHNCHI_H
#define JOHNCHI_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<ev.h>
#include<time.h>

#define ROW 9
#define COLUMN 9
#define RECORD 500
#define S 1

struct match{
    int bx,by,ax,ay;
    char chess;
    struct match *next , *pre;
};
typedef struct match Match;
Match *first,*current,*previous,*space;
int i,j,count,flag=0;
char tempX;
int selectX,selectY,targetX,targetY;
char temp;
char chessboard[ROW][COLUMN];
FILE *fptr;
extern char *optarg;
extern int optind,opterr,optopt;

void chessSetup();
void chessprint();
void chessinput();
void inputcheck();
void input_sl_again();
void input_tg_again();
void roundjudge();
void chessmove();
int moverule();
int movecheck();
void chesseat();
int winlose();
void regret_save();
void roundmove();

void timer();

ev_timer time_watcher;
ev_io io_watcher;
time_t tx=0,ty=0,tx1, tx2, ty1, ty2;

#endif