#include "../inc/johnchi.h"
#include "../inc/timer.h"

Match *first,*current,*previous,*space;
int i,j,count,flag=0;
char tempX;
int selectX,selectY,targetX,targetY;
char temp;
char chessboard[ROW][COLUMN];
FILE *fptr;


//move to the next or previous  round 
void roundmove(){
	int x;
	char ins;
	count=0;
	flag=-1;

	for(x=0;!feof(fptr);x++){
		current=(Match*) malloc(sizeof(Match));
		fscanf(fptr,"%d %d %d %d %c",&current->bx,&current->by,&current->ax,&current->ay,&current->chess);
		if(x==0) {
			first=current;
		}
		else {
			previous->next=current;
		}
		current->next=NULL;
		current->pre=previous;
		previous=current;
	} // load the chess in the file
	current=first;
	while(ins!='e'){
		chessprint();
		printf("Enter 'e' to exit\n");
		printf("Enter 'f' to go next or 'b' to go back : ");
		scanf("%c",&ins);
		getchar();
		switch(ins){
		case 'f':
			if(count>x-2){
				printf("This is the final round already ! \n");
				sleep(S);
			}
			else{
				chessboard[current->ay][current->ax]=chessboard[current->by][current->bx];
				chessboard[current->by][current->bx]='t';
				count++;
				current=current->next;
			}
			break;
		case 'b':
			if(count<1){
				printf("This is the first round already ! \n");
				sleep(S);
			}
			else{
				count--;
				chessboard[current->by][current->bx]=chessboard[current->ay][current->ax];
				chessboard[current->ay][current->ax]=current->chess;
				current=current->pre;
			}
			break;
		case 'e':
			return;
		default:
			printf("Not support the option ! \n");
			sleep(S);
			break;
		}
		system("clear");
	}
}

//back to the previous step or save the process of playing
void regret_save(){
	switch(tempX){
	case '0':
		if(count>1){
			count--;
			chessboard[current->by][current->bx] = chessboard[current->ay][current->ax];
			chessboard[current->ay][current->ax] = current->chess;
			space = current;
			current = previous->pre;
			previous = previous->pre;
			previous->next = NULL;
			free(space);
		}
		else if(count==1){
			count--;
			chessboard[current->by][current->bx] = chessboard[current->ay][current->ax];
			chessboard[current->ay][current->ax] = current->chess;
			space = current;
			current->next = NULL;
			previous = current->pre;
			free(space);
		}
		else{
			printf("You haven't move a chess ! \n");
			sleep(S);
		}
		getchar();
		count--;
		flag=0;
		break;
	case 's':
	case 'S':
		current=first;
		for(i=0;i<count;i++){
			fprintf(fptr,"%d %d %d %d %c\n",current->bx,current->by,current->ax,current->ay,current->chess);
			current=current->next;
		}
		fflush(fptr);
		printf("Save the game succesfully ! \n");
		sleep(S);
		getchar();
		count--;
		flag=0;
		break;
	}
}

//decide if the game is over
int winlose(){
	int win=0;
	
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(chessboard[i][j]=='K') win++;
			else if(chessboard[i][j]=='k') win+=2;
		}
	}
	return win;
}

//eat the chess
void chesseat(){
	switch(chessboard[selectY][selectX]){
		case 'L':
		case 'N':
		case 'S':
		case 'G':
		case 'K':
		case 'R':
		case 'B':
		case 'P':
			switch(chessboard[targetY][targetX]){
				case 'l':
				case 'n':
				case 's':
				case 'g':
				case 'k':
				case 'r':
				case 'b':
				case 'p':
					chessboard[targetY][targetX]=chessboard[selectY][selectX];
					chessboard[selectY][selectX]='t';
					break;
				case 't':
					temp=chessboard[targetY][targetX];
					chessboard[targetY][targetX]=chessboard[selectY][selectX];
					chessboard[selectY][selectX]=temp;
					break;
				default:
					printf("This is your chess ! \n");
					sleep(S);
					flag=2;
					count--;
					break;
		}
		break;
		case 'l':
		case 'n':
		case 's':
		case 'g':
		case 'k':
		case 'r':
		case 'b':
		case 'p':
			switch(chessboard[targetY][targetX]){
				case 'L':
				case 'N':
				case 'S':
				case 'G':
				case 'K':
				case 'R':
				case 'B':
				case 'P':
					chessboard[targetY][targetX]=chessboard[selectY][selectX];
					chessboard[selectY][selectX]='t';
					break;	
				case 't':
					temp=chessboard[targetY][targetX];
					chessboard[targetY][targetX]=chessboard[selectY][selectX];
					chessboard[selectY][selectX]=temp;
					break;
				default:
					printf("This is your chess ! \n");
					sleep(S);
					flag=2;
					count--;
					break;
			}
			break;
	}
}

//check if during the movement of chess is stopped
int movecheck(){
	int block=0;
	switch(chessboard[selectY][selectX]){
		case 'L':
			for(i=selectY+1;i<targetY;i++){
				if(chessboard[i][selectX] == 't') continue;
				else block=1;
			}
			break;
		case 'l':
			for(i=selectY-1;i>targetY;i--){
				if(chessboard[i][selectX] == 't') continue;
				else block=1;
			}
			break;
		case 'R':
		case 'r':
			if(selectX == targetX){
				if(selectY>targetY){
					for(i=selectY-1;i>targetY;i--){
						if(chessboard[i][selectX] == 't') continue;
						else block=1;
					}
				}	
				else if(selectY<targetY){
					for(i=selectY+1;i<targetY;i++){
						if(chessboard[i][selectX] == 't') continue;
						else block=1;
					}			
				}
			}
			else if(selectY == targetY){
				if(selectX>targetX){
					for(j=selectX-1;j>targetX;j--){
						if(chessboard[selectY][j] == 't') continue;
						else block=1;
					}
				}	
				else if(selectX<targetX){
					for(j=selectX+1;j<targetX;j++){
						if(chessboard[selectY][j] == 't') continue;
						else block=1;
					}			
				}
			}
			break;
		case 'B':
		case 'b':
			for(i=selectY-1,j=selectX+1;targetY-i<0 && targetX-j>0;i--,j++){
				if(chessboard[i][j] == 't') continue;
				else block=1; 
			}
			for(i=selectY-1,j=selectX-1;targetY-i<0 && targetX-j<0;i--,j--){
				if(chessboard[i][j] == 't') continue;
				else block=1; 
			}
			for(i=selectY+1,j=selectX-1;targetY-i>0 && targetX-j<0;i++,j--){
				if(chessboard[i][j] == 't') continue;
				else block=1; 
			}
			for(i=selectY+1,j=selectX+1;targetY-i>0 && targetX-j>0;i++,j++){
				if(chessboard[i][j] == 't') continue;
				else block=1; 
			}
			break;
	}
	return block;
}

//the rule of the movement
int moverule(){
	int crt=0;
	switch(chessboard[selectY][selectX]){
		case 'L':
			if((selectX == targetX) && (selectY < targetY)) crt=1;
			break;
		case 'l':
			if((selectX == targetX) && (selectY > targetY)) crt=1;
			break;
		case 'N':
			if(targetX == selectX+1 || targetX == selectX-1)
				if(targetY == selectY+2) crt=1;
			break;
		case 'n':
			if(targetX == selectX+1 || targetX == selectX-1)
				if(targetY == selectY-2) crt=1;
			break;
		case 'S':
			if((targetY == selectY+1) && (targetX == selectX || targetX == selectX+1 || targetX == selectX-1)) crt=1;
			else if((targetY == selectY-1) && (targetX == selectX+1 || targetX == selectX-1)) crt=1;
			break;
		case 's':
			if((targetY == selectY-1) && (targetX == selectX || targetX == selectX+1 || targetX == selectX-1)) crt=1;
			else if((targetY == selectY+1) && (targetX == selectX+1 || targetX == selectX-1)) crt=1;
			break;
		case 'G':
			if(targetY == selectY || targetY == selectY+1 || targetY == selectY-1){
				if(targetX == selectX || targetX == selectX+1 || targetX == selectX-1){
					if((targetY == selectY-1) && (targetX == selectX-1)) crt=0;
					else if((targetY == selectY-1) && (targetX == selectX+1)) crt=0;
					else crt=1;
				}
			}
			break;
		case 'g':
			if(targetY == selectY || targetY == selectY+1 || targetY == selectY-1){
				if(targetX == selectX || targetX == selectX+1 || targetX == selectX-1){
					if((targetY == selectY+1) && (targetX == selectX-1)) crt=0;
					else if((targetY == selectY+1) && (targetX == selectX+1)) crt=0;
					else crt=1;
				}
			}
			break;
		case 'K':
		case 'k':
			if(targetY == selectY || targetY == selectY+1 || targetY == selectY-1)
				if(targetX == selectX || targetX == selectX+1 || targetX == selectX-1) crt=1;
			break;
		case 'P':
			if(targetY == selectY+1)
				if(targetX == selectX) crt=1;
			break;
		case 'p':
			if(targetY == selectY-1)
				if(targetX == selectX) crt=1;
			break;
		case 'R':
		case 'r':
			if((targetY == selectY) || (selectX == targetX)) crt=1;
			break;
		case 'B':
		case 'b':
			if(abs(targetY-selectY) == abs(targetX-selectX)) crt=1;
			break;
	}
	return crt;
}

//move the chess and save
void chessmove(){
	int mr = moverule();
	int mc = movecheck();
	
	if(mr==1 && mc==0){
		current=(Match*) malloc(sizeof(Match));
		current->bx=selectX;current->by=selectY;current->ax=targetX;current->ay=targetY;
		current->chess=chessboard[targetY][targetX];
		if(count==0){
			first=current;
		}
		else{
			previous->next=current;
		}
		current->next=NULL;
		current->pre=previous;
		previous=current;
		chesseat();
	}
	else if(mr==0 || mc==1){
		printf("Wrong movement! \n");
		sleep(S);
		flag=2;
	}
}

//decide if the player move the other player's chess 
void roundjudge(){
	if(count%2==0){
		switch(chessboard[selectY][selectX]){
			case 'L':
			case 'N':
			case 'S':
			case 'G':
			case 'K':
			case 'R':
			case 'B':
			case 'P':
				printf("This is not your chess ! \n");
				sleep(S);
				flag=2;
				break;
			default:
				return;
		}
	}
	else if(count%2==1){
		switch(chessboard[selectY][selectX]){
			case 'l':
			case 'n':
			case 's':
			case 'g':
			case 'k':
			case 'r':
			case 'b':
			case 'p':
				printf("This is not your chess ! \n");
				sleep(S);
				flag=2;
				break;
			default:
				return;
		}
	}
}

//check the input
void inputcheck(){
	getchar();
	if(chessboard[selectY][selectX] == 't'){
		printf("There is no chess ! \n");
		sleep(S);
		flag=2;
	}
	else if((flag==1 || flag==3) && (targetX<0 || targetX>8 || targetY<0 || targetY>8)){
		printf("Beyond the border of the chessboard ! \n");
		sleep(S);
		flag=3;
	}
	else if(selectX>=0 && selectX<=8 && selectY>=0 && selectY<=8){
		return;
	}
	else if(selectX<0 || selectX>8 || selectY<0 || selectY>8){
		printf("Beyond the border of the chessboard ! \n");	
		sleep(S);
		flag=2;
	}
	else{
		printf("Not support the option ! \n");
		sleep(S);
		flag=0;
	}
}


//input the coordinate of chess and check
void chessinput(){
	if(flag==0 || flag==2){
		scanf("%c",&tempX);
		regret_save();
		selectX=tempX-48;
		if(tempX=='0' || tempX=='s' || tempX=='S')	return;
		if(selectX/10==0){
			scanf("%d",&selectY);
			selectY=selectY-1;
			selectX=9-selectX;
		}
		else{
			selectY=selectX%10-1;
			selectX=9-selectX/10;
		}
		flag=1;
		roundjudge();
		inputcheck();
	}
	else if(flag==1){
		scanf("%d",&targetX);
		if(targetX/10==0){
			scanf("%d",&targetY);
			targetY=targetY-1;
			targetX=9-targetX;
		}
		else{
			targetY=targetX%10-1;
			targetX=9-targetX/10;
		}
		flag=0;
		inputcheck();
		chessmove();
	}
	else if(flag==3){
		sleep(S);
		scanf("%d",&targetX);
		if(targetX/10==0){
			scanf("%d",&targetY);
			targetY=targetY-1;
			targetX=9-targetX;
		}
		else{
			targetY=targetX%10-1;
			targetX=9-targetX/10;
		}
		inputcheck();
		chessmove();
	}
}

//print the chessboard
void chessprint(){
	printf("９ ８ ７ ６ ５ ４ ３ ２ １\n");
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			switch(chessboard[i][j]){
				case 'L':
					printf("\033[31m香\033[0m ");
					break;
				case 'l':
					printf("\033[34m香\033[0m ");
					break;
				case 'N':
					printf("\033[31m桂\033[0m ");
					break;
				case 'n':
					printf("\033[34m桂\033[0m ");
					break;
				case 'S':
					printf("\033[31m銀\033[0m ");
					break;
				case 's':
					printf("\033[34m銀\033[0m ");
					break;
				case 'G':
					printf("\033[31m金\033[0m ");
					break;
				case 'g':
					printf("\033[34m金\033[0m ");
					break;
				case 'K':
					printf("\033[31m王\033[0m ");
					break;
				case 'k':
					printf("\033[34m王\033[0m ");
					break;
				case 'B':
					printf("\033[31m角\033[0m ");
					break;
				case 'b':
					printf("\033[34m角\033[0m ");
					break;
				case 'R':
					printf("\033[31m飛\033[0m ");
					break;
				case 'r':
					printf("\033[34m飛\033[0m ");
					break;
				case 'P':
					printf("\033[31m步\033[0m ");
					break;
				case 'p':
					printf("\033[34m步\033[0m ");
					break;
				case 't':
					printf("﹒ ");
					break;
			}
		}
		switch(i){
			case 0:
				printf("１");
				break;
			case 1:
				printf("２");
				break;
			case 2:
				printf("３");
				break;
			case 3:
				printf("４");
				break;
			case 4:
				printf("５");
				break;
			case 5:
				printf("６");
				break;
			case 6:
				printf("７");
				break;
			case 7:
				printf("８");
				break;
			case 8:
				printf("９");
				break;
		}
		printf("\n");
	}
	if(count%2==0) printf("It's playerX's turn \n");
	else if(count%2==1) printf("It's playerY's turn \n");
	if(flag==0)	printf("Please enter the coordinate of the chess: ");
	else if(flag==1){
		printf("The chess you select: %d %d\n",9-selectX,selectY+1);
		printf("Please enter the  coordinate of the target: ");
	}
	else if(flag==2) printf("Please enter the coordinate of the chess again: ");
	else if(flag==3){
		printf("The chess you select: %d %d\n",9-selectX,selectY+1);
		printf("Please enter the coordinate of the target again: ");
	}
}
  //set up the chess board
void chessSetup(){
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			chessboard[i][j]='t';
		}
	}
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			switch(i){
				case 0:
				case 8:
					switch(j){
					case 0:
					case 8:
						if(i==0){
							chessboard[i][j] = 'L';  // 香車 Lance
							break;
						}
						else if(i==8){
							chessboard[i][j] = 'l';  
							break;
						}
					case 1:
					case 7:
						if(i==0){
							chessboard[i][j] = 'N';  // 桂馬 Knight
							break;
						}
						else if(i==8){
							chessboard[i][j] = 'n'; 
							break;
						}
					case 2:
					case 6:
						if(i==0){
							chessboard[i][j] = 'S';  // 銀將 Silver General
							break;
						}
						else if(i==8){
							chessboard[i][j] = 's';  
							break;
						}
					case 3:
					case 5:
						if(i==0){
							chessboard[i][j] = 'G';  // 金將 Gold General
							break;
						}
						else if(i==8){
							chessboard[i][j] = 'g'; 
							break;
						}
					case 4:
						if(i==0){
							chessboard[i][j] = 'K';  // 玉將 王將 King
							break;
						}
						else if(i==8){
							chessboard[i][j] = 'k';  
							break;
						}
					}
					break;
				case 1:
					switch(j){
					case 1:
						chessboard[i][j] = 'R';  //飛車Rook
						break;
					case 7:
						chessboard[i][j] = 'B';  // 角行Bishop
						break;
					}
					break;
				case 7:
					switch(j){
					case 1:
						chessboard[i][j] = 'b';  
						break;
					case 7:
						chessboard[i][j] = 'r';  
						break;
					}
					break;
				case 2:
				case 6:
					switch(j){
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
						if(i==2){
							chessboard[i][j] = 'P';  //步兵Pawn
							break;
						}
						else if(i==6){
							chessboard[i][j] = 'p';  //步兵Pawn
							break;
						}
					}
					break;
			}
		}
	}
    
}




// static void io_cb(EV_P_ ev_io *w, int revents)
// {
//     if(count%2==0){
//         tx=tx+(tx2-tx1);
//         tx1=tx;
//     }
//     else if(count%2==1){
//         ty=ty+(ty2-ty1); 
//         ty1=ty;
//     }
// 	ev_io_stop(EV_A_ w);
// 	ev_timer_stop(loop, &time_watcher);
// 	ev_break(loop, EVBREAK_ALL);
// }
// static void timer_cb(EV_P_ ev_timer *w, int revents)
// {
// 	if(count%2==0){
// 		tx2 = time(NULL);
// 		system("clear");
// 		printf("PlayerX's time : %ld\n", tx+(tx2-tx1));
// 		printf("PlayerY's time : %ld\n", ty+(ty2-ty1));
// 		fflush(stdout);
// 	}
// 	else if(count%2==1){
// 		ty2 = time(NULL);
// 		system("clear");
// 		printf("PlayerX's time : %ld\n", tx+(tx2-tx1));
// 		printf("PlayerY's time : %ld\n", ty+(ty2-ty1));
// 		fflush(stdout);
// 	}
// 	chessprint();
// 	fflush(stdout);
// }

// void timer()
// {
//     tx1 = time(NULL);
// 	ty1 = time(NULL);
//     tx2 = time(NULL);
//     ty2 = time(NULL);
// 	struct ev_loop *loop = EV_DEFAULT;
// 	ev_io_init(&io_watcher,io_cb,0,EV_READ);
// 	ev_io_start(loop, &io_watcher);
// 	ev_timer_init(&time_watcher,timer_cb,0,1);
// 	ev_timer_start(loop, &time_watcher);
// 	ev_run(loop, 0);
// }
