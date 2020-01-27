#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Riddle.h"


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
    shuffle_shore(r);
    return r;

}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle_shore(Riddle * r){
    srand(time(NULL));
    int i;
    for(i = NUMBER-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&r->shore[r->position][i], &r->shore[r->position][j]);

    }
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

char * get_item(int val){
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

int get_position_player(Riddle * r){
    int i,pos=0;

    for(i=0;i<NUMBER;i++){
        if(!strcmp(get_item(r->shore[r->position][i]),"Boatman")){
            pos=i;
        }
    }

    return pos;
}

BOOL cross_shore(Riddle* r){
    if(r==NULL){
        return FALSE;
    }

    int pos_player = get_position_player(r);
    r->shore[get_other_shore(r->position)][pos_player] = r->shore[r->position][pos_player];
    r->shore[r->position][pos_player] = -1;
    r->position = get_other_shore(r->position);


    return TRUE;

}

BOOL move_animal(int animal,Riddle* r){
    if(animal < 0 || animal >=NUMBER || r==NULL){
        return FALSE;
    }

    if(r->shore[r->position][animal]!=-1 && strcmp(get_item(r->shore[r->position][animal]),"Boatman")!=0){
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
        anim = get_item(r->shore[r->position][i]);
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
        printf("%s\n",get_item(r->shore[0][i]));
    }
    printf("\n");
    printf("::::::SHORE 2:::::::\n\n");
    for(i=0;i < NUMBER;i++){
        printf("%s\n",get_item(r->shore[1][i]));
    }

    printf("\n");

    printf("Items to move: \n");
    print_options(r);

}




