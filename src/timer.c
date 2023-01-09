#include "../inc/timer.h"

ev_timer time_watcher;
ev_io io_watcher;
time_t tx=0,ty=0,tx1, tx2, ty1, ty2;

static void io_cb(EV_P_ ev_io *w, int revents)
{
    if(count%2==0){
        tx=tx+(tx2-tx1);
        tx1=tx;
    }
    else if(count%2==1){
        ty=ty+(ty2-ty1); 
        ty1=ty;
    }
	ev_io_stop(EV_A_ w);
	ev_timer_stop(loop, &time_watcher);
	ev_break(loop, EVBREAK_ALL);
}
static void timer_cb(EV_P_ ev_timer *w, int revents)
{
	if(count%2==0){
		tx2 = time(NULL);
		system("clear");
		printf("PlayerX's time : %ld\n", tx+(tx2-tx1));
		printf("PlayerY's time : %ld\n", ty+(ty2-ty1));
		fflush(stdout);
	}
	else if(count%2==1){
		ty2 = time(NULL);
		system("clear");
		printf("PlayerX's time : %ld\n", tx+(tx2-tx1));
		printf("PlayerY's time : %ld\n", ty+(ty2-ty1));
		fflush(stdout);
	}
	chessprint();
	fflush(stdout);
}

void timer()
{
    tx1 = time(NULL);
	ty1 = time(NULL);
    tx2 = time(NULL);
    ty2 = time(NULL);
	struct ev_loop *loop = EV_DEFAULT;
	ev_io_init(&io_watcher,io_cb,0,EV_READ);
	ev_io_start(loop, &io_watcher);
	ev_timer_init(&time_watcher,timer_cb,0,1);
	ev_timer_start(loop, &time_watcher);
	ev_run(loop, 0);
}