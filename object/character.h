#include "character.c"

/*
 * This is a skeleton of a character
 * The only data will be stored in file are "DAT"
 * Since other information can be calculated by DAT
 */
// TODO: Character data should be shared with user such that they can do some calculations for server
//       Only thing that server needs to do is to update data with user
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
  int item[50]; //DAT  two section, one is item index for lookup, another is number
  int location; //DAT
}char_t;

/*
 * This function will first check if the character has been loaded
 * (the character is still reachable because play disconnect and reconnect)
 * If the character isn't loaded, check if the file has been mapped
 * If not, map the file that character is stored and load the character.
 * If char_id is -1 (new user), call create character function.
 * Return 0 on success, return -1 on failure.
 * NOTE: each file is design to hold 1000 character (or more, this config can be changed)
 */
int load_character(int char_id);


