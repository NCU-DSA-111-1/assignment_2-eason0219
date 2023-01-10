#ifndef JOHNCHI_H
#define JOHNCHI_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

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
extern Match *first,*current,*previous,*space;
extern int i,j,count,flag;
extern char tempX;
extern int selectX,selectY,targetX,targetY;
extern char temp;
extern char chessboard[ROW][COLUMN];
extern FILE *fptr;
extern char *optarg;
extern int optind,opterr,optopt;

void chessSetup();
void chessprint();
void chessinput();
void inputcheck();
void roundjudge();
void chessmove();
int moverule();
int movecheck();
void chesseat();
int winlose();
void regret_save();
void roundmove();

void timer();

#endif
