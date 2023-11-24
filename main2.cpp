#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h" 
#include "board.c" 
# define N_PLAYER 3
//3인용 게임이 되는거고 , 몇인용 게임할거니?  
#define MAX_DIE    6

#define PLAYERSTATUS_LIVE 0
#define PLAYERSTATUS_DIE 1
#define PLAYERSTATUS_END 2
#define MAX_CHARNAME 200
//죽은거 끝까지 간거 =2 plyaer status is represented as integers macro has been ddefined
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
int game_end(void){
	int i;
	int flag_end=1;
	
	//if all the players are died
	for (i=0;i<N_PLAYER;i++){
		if (player_status[i]==PLAYERSTATUS_LIVE)
		{
			flag_end=0;
			break;
		}
	}
	return flag_end;
}

int getAlivePlayer(void){
	int i;
	int cnt=0;
	for(i=0;i<N_PLAYER;i++){
		if (player_status[i]==PLAYERSTATUS_END)
		cnt++;
	}
	return cnt;
}

int getWinner(void){
	int i;
	int winner=0;
	int max_coin=-1;
	
	for(i=0;i<N_PLAYER;i++){
		if(player_coin[i]>max_coin){
			max_coin=player_coin[i];
			winner=i;
		}
	}
	return winner;
}
int main(int argc, char *argv[]) {
    int pos = 0;
    int i;
    int turn = 0;
    srand((unsigned)time(NULL));

    // Opening function
    opening();

    // Initialize board and players
    board_initboard();
    for (i = 0; i < N_PLAYER; i++) {
        player_position[i] = 0;
        player_coin[i] = 0;
        player_status[i] = PLAYERSTATUS_LIVE;
        printf("Player %i's name: ", i);
        scanf("%s", player_name[i]);
    }

    // Game loop
    while (!game_end()) {
        int step;
        int coinResult;
        int pos;
        char c;

        // Skip turn if player is not alive
        if (player_status[turn] != PLAYERSTATUS_LIVE) {
            turn = (turn + 1) % N_PLAYER;
            continue;
        }

        // Board and player status
        board_printBoardStatus();
        for (i = 0; i < N_PLAYER; i++) {
            printPlayerPosition(i);
        }
        printPlayerStatus();

        // Roll the dice
        printf("%s's turn. Press any key\n", player_name[turn]);
        scanf("%d", &c);
        fflush(stdin);
        step = rolldie();

        // Move player
        player_position[turn] += step;
        if (player_position[turn] >= N_BOARD) {
            player_position[turn] = N_BOARD - 1;
        }

        // Update player status
        player_status[turn] = PLAYERSTATUS_END;

        // Get coin
        coinResult = board_getBoardCoin(pos);
        player_coin[turn] += coinResult;

        // Next player's turn
        turn = (turn + 1) % N_PLAYER;

        // Shark attack and check for players' status
        if (turn == 0) {
            int shark_pos = board_stepShark();
            checkDie();
        }

        // Print number of players still alive
        printf("Alive Players: %d\n", getAlivePlayer());
    }

    // After game ends
    int winner = getWinner();
    printf("Game over. The winner is Player %d\n", winner);

    // Pause the system for the user to see the result
    system("PAUSE");
    return 0;
}



