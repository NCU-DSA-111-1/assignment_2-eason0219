#include "../inc/johnchi.h"
#include "../inc/timer.h"

void main(int argc, char *argv[]){
	int ch;
	int status=0;

	while((ch=getopt(argc,argv,"ns:l:")) != -1){
		switch(ch){
			case 'n': // -n : new game
				status=1;
				break;
			case 's': // -s [file name] : locaton of saving the game
				fptr=fopen(optarg,"w+");
				if(fptr==NULL){
					printf("File cannot be opened ! ");
					return;
				}
				break;
			case 'l': // -l [file name] : location of loading the game
				fptr=fopen(optarg,"r+");
				if(fptr==NULL){
					printf("File cannot be opened ! ");
					return;
				}
				status=2;
				break;
			default:
				printf("Not support the option ! \n");
				return;
		}
	}
	if(status==1){
		count=0;
		chessSetup();
		while(count<RECORD){
			if(winlose()==3 || winlose()==0){
				timer();
				chessinput();
				while(flag==1 || flag==2 || flag==3){
					timer();
					chessinput();
				}
				count++;
			}
			else if(winlose()==1){ 
				system("clear");
				flag=-1;
				chessprint();
				printf("The winner is player Y ! \n");
				printf("PlayerX's time : %ld\n", tx+(tx2-tx1));
				printf("PlayerY's time : %ld\n", ty+(ty2-ty1));
				break;
			}
			else if(winlose()==2){ 
				system("clear");
				flag=-1;
				chessprint();
				printf("The winner is player X ! \n");
				printf("PlayerX's time : %ld\n", tx+(tx2-tx1));
				printf("PlayerY's time : %ld\n", ty+(ty2-ty1));
				break;	
			}
		}
	}
	else if(status==2){
		system("clear");
		chessSetup();
		roundmove();
	}
	fclose(fptr);
}