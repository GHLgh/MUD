#include <string.h>
#include "login.h"

// TODO: what if the file is too big??
int map_userinfo(char* filename){
  int fd = open(filename, O_RDONLY);
  if(fd == -1){
    fprintf(stderr, "Cannot open %s\n", filename);
    return -1;
  }
  int size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);

  void* addr = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
  close(fd);
  if(addr == (void *) -1){
    fprintf(stderr, "Failed to map %s\n", filename);
    return -1;
  }

  char* head = addr;
  if(strncmp(head, "UERF", 4)!=0){
    formatFail(argv[1]);
    exit(2);
  }
}

// find_user function will take username that client provided, the length of the username and current position (a int pointer)
// Return 1 and update current position if the username is found (charactr has been created)
// Return 0 otherwise
// The user_info file will be mapped into memory using mmap when setup the server
int find_user(char* username, int len, int* curr_pos){

}

int login(int fd){
  char buffer[MSG_SIZE];
  int len = 0;
  int num;
  int user_status = 0; // 1: found username 0: username does not exist
  int curr_pos = 0; // use to keep track on the current position in mmap
  while(user_status == 0){
    while (1) {
      num = read(fd, buffer + len, MSG_SIZE);
      len += num;
      if (!num) {
        client_is_connected = 0;
        break;
      }
      if (buffer[len-1] == '\n')
        buffer[len-1] = 0;
        break;
    }
    if(strcmp(buffer, "exit") == 0)
      return -1;

    char username[len];
    strcpy(username, buffer);
    user_status = find_user(username, len, &curr_pos);
    
  }
}
