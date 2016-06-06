#include "character.c"

/*
 * This is a skeleton of a character which also will be used on monsters in the dungeon
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
  int equipment[3]; //DAT weapon, armor, talisman
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
 * Return index on character array on success, return -1 on failure.
 * NOTE: each file is design to hold 1000 character (or more, this config can be changed)
 */
int load_character(int char_id);

/*
 * This is opposite of load_character function.
 * It will be called when an inactive character in the character array is replaced
 * (inside load_character and when the server is shutting down??)
 * flag option: 0 - "soft" call, write back when mmap is mapping at the right file
 *                  (when user chooses to log off)
 *              1 - "hard" call, map to the corresponing file and write back
 *                  (when load_character and shut_down called)
 * Return 0 on success and -1 on failure
 */
int store_character(int index, int flag);

/*
 * This function will be called in load_character function
 * Return corresponding character_id on success, -1 on failure
 * TODO: The server will need a status(log) file to store overall information
 *       In this case, such that correct character_id can be returned
 */
int create_character();

/*
 * This function will be called when the server is going to shut down
 * Basically writing every object in character array back to file
 */
void clean_up();
