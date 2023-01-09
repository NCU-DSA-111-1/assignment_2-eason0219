#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <ev.h>
#include "johnchi.h"

extern int count;
extern void chessprint();

extern ev_timer time_watcher;
extern ev_io io_watcher;
extern time_t tx,ty,tx1, tx2, ty1, ty2;

#endif