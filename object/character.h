#include "character.c"

/*
 * This is a skeleton of a character
 * The only data will be stored in file are "DAT"
 * Since other information can be calculated by DAT
 */

typedef struct _character_t{
  char* name; //DAT
  int species; //DAT use as a factor when calculating the character data
  int status; //DAT buff/debuff, usage is similar to species
  int lv;
  int exp; //DAT
  int atk;
  int spd;
  int hp; //DAT
  int max_hp;
  int equipment[3]; //DAT weapon, armor, talisman (HP trick)
  int capacity; // weight
  int max_capacity;
  int item[100]; //DAT
  int location; //DAT
}char_t;

/*
 * This function 
 *
 *
 *
 */

int load_character(int char_id);
