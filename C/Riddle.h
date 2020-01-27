#ifndef RIDDLE_H_INCLUDED
#define RIDDLE_H_INCLUDED

#define BOOL int
#define TRUE 0
#define FALSE 1
#define NUMBER 4
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


Riddle* create_riddle(void);
void destroy_riddle(Riddle * r);
void swap(int *a, int *b);
void shuffle_shore(Riddle * r);
int get_other_shore(int pos);
char * get_item(int val);
BOOL game_succes(Riddle * r);
int get_position_player(Riddle * r);
BOOL cross_shore(Riddle* r);
BOOL move_animal(int animal,Riddle* r);
BOOL game_failure(Riddle * r);
void print_options(Riddle *r);
void print_game(Riddle * r);


#endif // RIDDLE_H_INCLUDED
