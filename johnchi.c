#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

#define ROW 9
#define COLUMN 9
#define RECORD 500
#define S 2

int i,j;
char tempX;
int selectX,selectY,targetX=5,targetY=5;
char temp;
char chessboard[ROW][COLUMN];
int count;
char chess[RECORD];
int bx[RECORD],by[RECORD],ax[RECORD],ay[RECORD];
extern char *optarg;
extern int optind,opterr,optopt;
File *fptr;

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
char winlose();
void chessregret();
void


void main(int argc, char *argv[]){
	chessSetup();
    for(count=0;count<RECORD;count++){
    	system("clear");
    	chessprint();
   		if(winlose()==3 || winlose()==0){
   			chessinput();
 			chessmove();
   		}
   		else if(winlose()==1){ 
  			printf("The winner is player Y ! \n");
   			break;
   		}
   		else if(winlose()==2){ 
   			printf("The winner is player X ! \n");
   			break;	
   		}
   	}
}

//back to the previous step 
void chessregret(){
	while(tempX == '0' && count>0){
		count--;
		chessboard[by[count]][bx[count]]=chessboard[ay[count]][ax[count]];
		chessboard[ay[count]][ax[count]]=chess[count];
		system("clear");
		chessprint();
		printf("Please enter the X coordinate of the chess : ");
		scanf("%c",&tempX);
		getchar();
		selectX=9-(tempX-48);
	}
}

//decide if the game is over
char winlose(){
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
			system("clear");
			chessinput();
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
			system("clear");
			chessprint();
			chessinput();
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
		bx[count]=selectX;by[count]=selectY;ax[count]=targetX;ay[count]=targetY;
		chess[count]=chessboard[targetY][targetX];
		chesseat();
	}
	else if(mr==0 || mc==1){
		printf("Wrong movement! \n");
		sleep(S);
		system("clear");
		chessprint();
		chessinput();
		chessmove();	
	}
}

//decide if the player move the other player's chess 
void roundjudge(){
	while(count%2==0){
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
			input_sl_again();
			break;
		default:
			return;
		}
	}
	while(count%2==1){
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
			input_sl_again();
			break;
		default:
			return;
		}
	}
}

//check the input
void inputcheck(){
	while(selectX<0 || selectX>8 || selectY<0 || selectY>8){
		printf("Beyond the border of the chessboard ! \n");
		input_sl_again();
		roundjudge();
		inputcheck();
	}
	while(chessboard[selectY][selectX] == 't'){
		printf("There is no chess ! \n");
		input_sl_again();
		roundjudge();
		inputcheck();
	}
	while(targetX<0 || targetX>8 || targetY<0 || targetY>8){
		printf("Beyond the border of the chessboard ! \n");
		input_tg_again();
	}
}

//input select again
void input_sl_again(){
	sleep(S);
	system("clear");
	chessprint();
	getchar();
	printf("Please enter the X coordinate of the chess again: ");
	scanf("%c",&tempX);
	getchar();
	selectX=9-(tempX-48);
	printf("Please enter the Y coordinate of the chess again: ");
	scanf("%d",&selectY);
	selectY=selectY-1;	
}

//input target again
void input_tg_again(){
	sleep(S);
	printf("Please enter the X coordinate of the target again : ");
	scanf("%d",&targetX);
	printf("Please enter the Y coordinate of the target again : ");
	scanf("%d",&targetY);
	targetX=9-targetX;
	targetY=targetY-1;
}

//input the coordinate of chess and check
void chessinput(){
	printf("Please enter the X coordinate of the chess : ");
	scanf("%c",&tempX);
	getchar();
	chessregret();
	selectX=9-(tempX-48);
	printf("Please enter the Y coordinate of the chess : ");
	scanf("%d",&selectY);
	selectY=selectY-1;
	roundjudge();
	inputcheck();
	printf("Please enter the X coordinate of the target : ");
	scanf("%d",&targetX);
	targetX=9-targetX;
	printf("Please enter the Y coordinate of the target : ");
	scanf("%d",&targetY);
	targetY=targetY-1;
	getchar();
	inputcheck();
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
	if(count%2==0) printf("It's player X's turn \n");
	else if(count%2==1) printf("It's player Y's turn \n");
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
