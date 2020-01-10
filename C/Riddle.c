#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOOL int
#define TRUE 0
#define FALSE 1
#define NUMBER 4
#define PLAYER 0
#define SHORE 2

/*
0 -> Boatman

1 -> Goat

2-> cabbage

3-> Wolf
*/

typedef struct _Riddle {
    int shore[SHORE][NUMBER];
    int position;
    int flag;
} Riddle;

Riddle* create_riddle(void){

    Riddle* r = NULL;
    int i;

    r = (Riddle*) malloc(sizeof(Riddle));
    if(r==NULL){
        return NULL;
    }

    for(i=0;i<NUMBER;i++){
        r->shore[0][i] = i;
        r->shore[1][i]= -1;
    }

    r->position = 0;
    r->flag = 0;

    return r;

}

void destroy_riddle(Riddle * r){
    if(r==NULL){
        return;
    }

    free(r);
    r = NULL;

    return;
}
int get_other_shore(int pos){
    if (pos==0){
        return 1;
    }

    return 0;

}

char * get_animal(int val){
    switch(val){
        case 0:
            return "Boatman";
        case 1:
            return "Goat";
        case 2:
            return "Cabbage";
        case 3:
            return "Wolf";
        default:
            return " ";
    }


}
BOOL game_succes(Riddle * r){
    int total=0,i;

    if(r==NULL){
        return TRUE;
    }

    for(i=0;i<NUMBER;i++){
            total += r->shore[1][i];
    }

    if(total == 6){
        r->flag=1;
        return TRUE;
    }

return FALSE;

}

BOOL cross_shore(Riddle* r){
    if(r==NULL){
        return FALSE;
    }

    r->shore[get_other_shore(r->position)][PLAYER] = r->shore[r->position][PLAYER];
    r->shore[r->position][PLAYER] = -1;
    r->position = get_other_shore(r->position);


    return TRUE;

}

BOOL move_animal(int animal,Riddle* r){
    if(animal < 0 || animal >=NUMBER || r==NULL){
        return FALSE;
    }

    if(r->shore[r->position][animal]!=-1 && strcmp(get_animal(r->shore[r->position][animal]),"Boatman")!=0){
            r->shore[get_other_shore(r->position)][animal] = r->shore[r->position][animal];
            r->shore[r->position][animal] = -1;
        }

    cross_shore(r);
    return TRUE;
}



BOOL game_failure(Riddle * r){
    int total=0,i;

    if(r==NULL){
        return TRUE;
    }

    if(r->position == 0){
        for(i=0;i<NUMBER;i++){
            total += r->shore[get_other_shore(r->position)][i];
        }
    }else{
        for(i=0;i<NUMBER;i++){
            total += r->shore[get_other_shore(r->position)][i];
        }
    }
    if(total == 2 || total == 1){
        r->flag = -1;
        return TRUE;
    }

    return FALSE;
}

void print_options(Riddle *r){
    int i;
    char* anim;
    for(i = 0; i<NUMBER;i++){
        anim = get_animal(r->shore[r->position][i]);
        if(strcmp(anim," ")){
            printf("%d - %s\n",i+1,anim);
        }
    }
    return;
}

void print_game(Riddle * r){

    int i;

    printf("--It is on the shore %d-- \n\n",r->position + 1);
    printf("::::::SHORE 1:::::::\n\n");
    for(i=0; i < NUMBER;i++){
        printf("%s\n",get_animal(r->shore[0][i]));
    }
    printf("\n");
    printf("::::::SHORE 2:::::::\n\n");
    for(i=0;i < NUMBER;i++){
        printf("%s\n",get_animal(r->shore[1][i]));
    }

    printf("\n");

    printf("Items to move: \n");
    print_options(r);

}

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

