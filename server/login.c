#include <string.h>
#include <stdio.h>

#include "login.h"

// TODO: protantially needs a mutex for new_user

static char* userinfo;
// TODO: what if the file is too big??
// Assume the file provided is user info file
int map_userinfo(char* filename){
  FILE* fd = fopen(filename, r);
  if(fd == NULL){
    fprintf(stderr, "Cannot open %s\n", filename);
    return -1;
  }
  userinfo = malloc(strlen(filename)+1);
  strcpy(userinfo, filename);
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
    user_array[user_num-1].user_status = 0;
    // The new allocated line becomes: username\0password\0ch_id\0
    // So when it is time to free heap memory, free(usrename) should be sufficient
  }
  fclose(fd);
  return 0;
}

void unmap_userinfo(){
  FILE* fd = fopen(userinfo, a);
  int i = 0;
  for(; i < user_num; i++){
    if(user_array[i].user_status)
      fprintf(fd, "%s,%s,%d\n", user_array[i].username,user_array[i].password,user_array[i].character_id);
    free(user_array[i].username);
  }
  free(user_array);
  fclose(fd);
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

// match_password function is used for user auth
// there are three tries for each login
// old user: get password temp from user_array
// TODO: new user: get password temp by asking user for a password
// then ask user for password to match the password temp
// on success, return index (new user will enlarge the user_array and return the new index)
// on failure, return -1
// TODO: make read from client a function
int match_password(int index, char* new_user){
  int i = 0;
  for(; i < 3; i++){
    write(fd, PASSWORD, strlen(PASSWORD));
    char buffer[MSG_SIZE];
    int len = 0;
    int num;
    while (1) {
      num = read(fd, buffer + len, MSG_SIZE);
      len += num;
      if (!num)
        return -1;
      if (buffer[len-1] == '\n')
        buffer[len-1] = 0;
        break;
    }
    if(index == -1){
      char* user = malloc(strlen(buffer)+strlen(new_user)+6);
      sprintf(user, "%s,%s,%d", new_user,buffer,-1);

      user_num++;
      realloc(user_array, sizeof(user_info)*user_num);
      user_array[user_num-1].username = strsep(&user, ",");
      user_array[user_num-1].password = strsep(&user, ",");
      user_array[user_num-1].character_id = atoi(user);
      user_array[user_num-1].user_status = 1;
      return user_num-1;
    }
    else if(strcmp(buffer, user_array[index].password)==0)
      return index;
  }
  return -1;
}

int login(int fd){
  char buffer[MSG_SIZE];
  int len = 0;
  int num;
  int user_status = -1; // -1: username does not exist / mismatch. Otherwise, corresponding position in user_array
  char* new_user = NULL;
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
    if(user_status == -1)
      write(fd, NEWUSER, strlen(NEWUSER));
    user_status = match_password(user_status, buffer);
  }
  return user_array[user_status].character_id;
}
