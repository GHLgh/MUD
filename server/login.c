#include <string.h>
#include <stdio.h>

#include "login.h"

// TODO: what if the file is too big??
// Assume the file provided is user info file
int map_userinfo(char* filename){
  FILE* fd = fopen(filename, r);
  if(fd == NULL){
    fprintf(stderr, "Cannot open %s\n", filename);
    return -1;
  }
  char* buffer = NULL;
  size_t size = 0;
  ssize_t len = 0;
  while((len = getline(&buffer, &size, fd))!=-1){
    // Tokenize the line obtained. line format: username,password,ch_id\n
    if(buffer[len-1]=='\n')
      buffer[len-1] = 0;
    char* user = malloc(strlen(buffer)+1);
    strcpy(user, buffer);

    user_num++;
    realloc(user_array, sizeof(user_info)*user_num);
    user_array[user_num-1].username = strsep(&user, ",");
    user_array[user_num-1].password = strsep(&user, ",");
    user_array[user_num-1].character_id = atoi(user); 
    // The new allocated line becomes: username\0password\0ch_id\0
    // So when it is time to free heap memory, free(usrename) should be sufficient
  }
  return 0;
}

// find_user function will take username that client provided and the length of the username
// Return -1 if the username is not found
// Return corresponding index in user_array otherwise
// The user_info file will be mapped into memory when setup the server
int find_user(char* username){
  int index = 0;
  for(; index < user_num, index++){
    if(strcmp(username, user_array[index].username)==0)
      return index;
  }
  return -1;
}

int login(int fd){
  char buffer[MSG_SIZE];
  int len = 0;
  int num;
  int user_status = -1; // -1: username does not exist / mismatch. Otherwise, corresponding position in user_array
  while(user_status == -1){
    write(fd, USERNAME, strlen(USERNAME));
    while (1) {
      num = read(fd, buffer + len, MSG_SIZE);
      len += num;
      if (!num)
        return -1; // TODO: check what needs to be done if client d/c abnormally

      if (buffer[len-1] == '\n')
        buffer[len-1] = 0;
        break;
    }
    if(strcmp(buffer, "exit") == 0)
      return -1;

    user_status = find_user(buffer);
    // TODO: check password / create new user if not found
  }
}
