#include <stdio.h>
#include <stdlib.h>
#include "Riddle.h"

int main()
{

    int inp_use;
    printf("Welcome to \'The riddle of the wolf, the goat and the cabbage\'\n\n");

    Riddle * game = create_riddle();

   do{
        print_game(game);
        printf("Select one of the following options\n");
        printf("1 - Cross river\n");
        printf("2 - Move item to the other shore\n");
        printf("Input:");
        scanf("%d",&inp_use);
        if(inp_use == 1){
            cross_shore(game);
        }else{
                printf("Select which item you want to move from the list of available:");
                scanf("%d",&inp_use);
                move_animal(inp_use-1,game);
        }
       system("cls");
    }while(game_failure(game)==FALSE && game_succes(game)==FALSE);

    if(game->flag==1){
        printf("You have solved the riddle!!");
    }else{
        printf("You haven't managed to solve the riddle..");
    }
    destroy_riddle(game);

    return 0;
   }
