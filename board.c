#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#define N_BOARD    15 //board 칸 
#define N_COINPOS     12
#define MAX_COIN   4
#define SHARK_INITPOS -4
#define MAX_SHARKSTEP 6


// 상어에 의한 보드의 파손 여부 
int board_status[N_BOARD];

//i번째 칸이 가진 coin 수 
int board_coin[N_BOARD];

//상어 위치
static int board_sharkPosition; 

// 초기화 board 
int board_initboard(void)
{
    int i;
    for(i=0;i<N_BOARD;i++)
    {
        board_status[i] = BOARDSTATUS_OK;
        board_coin[i] = 0;                       
    }    
    
    board_sharkPosition = SHARK_INITPOS;
    
    for(i=0;i<N_COINPOS;i++)
    {
        int flag = 0;
        while(flag == 0)
        {
            int allocPos = rand()%N_BOARD;
            
            if(board_coin[allocPos] == 0)
            {
                 board_coin[allocPos] == rand()%MAX_COIN+1;     
                 flag = 1;                   
            }       
        }                        
    }
    return 0;
}

// print board status
int board_printBoardStatus(void)
{
    int i;
    
    printf("-------------------- BOARD STATUS --------------------\n");
//    ///?????????????????????????????????????



    for (i=0;i<N_BOARD;i++)
    {
        printf("|");
        if (board_status[i] == BOARDSTATUS_NOK)
           printf("X");
        else 
           printf("O");    
    }    
    printf("|\n");
    printf("------------------------------------------------------\n");
    return 0;
}

//board get coin
int board_getBoardCoin(int pos)
{
    int coin = board_coin[pos];
    board_coin[pos] = 0; 
    return coin;    
}

//get shark position
int board_getSharkPosition(void);

//step shark
int board_stepShark(void){
	int step=rand()%MAX_SHARKSTEP +1;
	int i;
	int shark_position;
	
	
	for (i=shark_position+1;i<=shark_position+step;i++)
	{
		if(i>=0 && i<N_BOARD)
		//negative positionfor the shark is nonresonable 
		board_status[i]=BOARDSTATUS_NOK;
		//already current position of the board has been destroyed and should be destroyed from the next step of its current poitn
	}
	shark_position +=step;
	
	return shark_position;
}

//보드 파손 여부 
int board_getBoardStatus(int pos) 
{
    return board_status[pos];    
}

//-> 이름 통일성 중요 
