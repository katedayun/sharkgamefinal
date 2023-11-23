#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h" 
#include "board.c" 
# define N_PLAYER 3
//3�ο� ������ �Ǵ°Ű� , ���ο� �����ҰŴ�?  
#define MAX_DIE    6

#define PLAYERSTATUS_LIVE 0
#define PLAYERSTATUS_DIE 1
#define PLAYERSTATUS_END 2
#define MAX_CHARNAME 200
//������ ������ ���� =2 plyaer status is represented as integers macro has been ddefined
//4 people playing [N_player][status has been ] charged
int player_position[N_PLAYER];
char player_name[N_PLAYER][200];
int player_coin[N_PLAYER];//coin how many con has been get
int player_status[N_PLAYER];
//exampel if(player_status[0]==PLAYERSTATUS_LIVE;
//N_player if for people is playing with array charged
//name is char upto 200 letters
char player_statusString[3][MAX_CHARNAME]={"LIVE","DIE","END"};
//I want to represent what the 0 1 2 each represents whether they are alive or die or end
//because human does not know what state it represents 
//up to here is modeling - program code specification .. 
//SET OF THE BOARD...
//for loop f
//0. opening function
void opening(void)
{
     printf("===========\n");
     printf("===========\n");
     printf("   shark   \n");
     printf("===========\n");
     printf("===========\n");
}

int rolldie(void)
{
    return rand()%MAX_DIE;
}

void printPlayerPosition(int player){
	int i;
	for (i=0;i<N_BOARD;i++){
		printf("|");
		if (i == player_position[player])
		//if my position is same as the board position 
			printf("%c",player_name[player][0]);
		else
		{
			if(board_getBoardStatus(i)==BOARDSTATUS_NOK )	
				printf("X");
			else 
				printf("");
					}
		
	}
	printf("|\n");
}

void printPlayerStatus(void){
	int i;
	printf("players status______\n");
	for(i=0;i<N_PLAYER;i++)
	{
		printf("%s: pos: %i, coint %i,status: %s\n",player_name[i], player_position[i],player_coin[i],player_statusString[player_status[i]]);
		//printing out - arrays are defined 
	}
	printf("------------\n");
}

void checkDie(void){
	int i;
	for (i=0;i<N_PLAYER;i++)
		if(board_getBoardStatus(player_position[i])==BOARDSTATUS_NOK)
			player_status[i]=PLAYERSTATUS_DIE;
			
}
int main(int argc, char *argv[])
{
  int pos=0;
  int i;
  int turn=0;
  //player no 0 starts from the first, because 1,2 the number ?? status of plyers should be notified
  // rand 초기화 함수
  srand((unsigned)time(NULL));
  // 0. opening 
  opening();
  //1. 초기화 및 플레이어 이름 설정
  board_initboard();
  //1-2. initialize players
  for (i=0;i<N_PLAYER;i++)
  //player n all initialzlized: all players
  {
  	player_position[i]=0;
  	player_coin[i]=0;
  	player_status[i]=PLAYERSTATUS_LIVE;
  	//player_name
  	printf("Player %i's name:",i);
  	scanf("%s",player_name[i]); // this form perfectly mathces to pointer thus do not use and "&" in scanf 
  	
  }
  //2. 반복문 (플레이어 턴)
  do
  {
       int step;
       int coinResult;
       int pos;
       char c;

	   if(player_status[turn]!=PLAYERSTATUS_LIVE)
	   {
	   	turn==(turn+1)%N_PLAYER;
	   	continue;
	   }

-
       //2-1. player status printing out 
       board_printBoardStatus();
       for(i=0;i<N_PLAYER;i++){
	   
	   		printPlayerPosition(i);
	   	}
	   		
       printPlayerStatus();
       
       //2-2. 주사위 던지기roll the dice
       printf("%s turn",player_name[turn]);
       printf("press any key\n");
       scanf("%d",&c);
       //scan any key
       fflush(stdin);
       //buffer ... piling buffer on keyboard..buffer flushing neccessary : flush the standard input output 
       step = rolldie();
       
       //2-3. 이동move
	   player_position[turn] += step;
	   if (player_position[turn]>=N_BOARD)
	   	player_position[turn]=N_BOARD-1;
	   //if N_Board number max set to 15? 0 to 14 : starting from the 15 needs to be wrong coice consdiered, i mean the number represents it move over the board
	       //printf();
	    player_status[turn]= PLAYERSTATUS_END;
     
       //2-4. get coin
    	coinResult = board_getBoardCoin(pos) ;  
    	player_coin[turn]+=coinResult;
    	
    	//coin has been extinguished and I get another ones
       //2-5. �next turn
       turn = (turn +1)%N_PLAYER; //wrap around 012 players repeated with the reamainder of the 3
       //next players roll the dice and ply
       //2-6. 상어 동작(조건 : 모든 플레이어가 한번씩 턴을 돔)
       if(turn==0)
       {
       	//shark attacking
		   int shark_pos=board_stepShark();
		   //printf();
		   checkDie(); 
	   }
       // |-> if(조건 : 모든 플레이어가 한번씩 턴을 돔) {상어 동작} 
  }while(1);
  //3. 정리 (승자계산 , 출력 등)   
  
  system("PAUSE");	
  return 0;
}
