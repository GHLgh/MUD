#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "login.h"

extern user_info* user_array; // import the variable in login.c to check if the output is correct

// TODO: not sure if it works
// This function will build a server and accept a connection (usually from fake client)
// Return the corresponding client file descriptor
int sock_fd; // server socket, set as global because it needs to be clean up lately

int easy_server(){
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  struct addrinfo hints, *result;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, "2333", &hints, &result);
  bind(sock_fd, result->ai_addr, result->ai_addrlen);
  listen(sock_fd, 10);
  freeaddrinfo(result);

  int client_fd = accept(sock_fd, NULL, NULL);

  return client_fd;
}

// This function will automatically connect to easy_server
// Return the connected file descriptor
int easy_client(){
  int client_sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  struct addrinfo hints, *result;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET; /* IPv4 only */
  hints.ai_socktype = SOCK_STREAM; /* TCP */

  getaddrinfo("127.0.0.1", "2333", &hints, &result);

  connect(client_sock_fd, result->ai_addr, result->ai_addrlen);

  return client_sock_fd;
}

int main(int argc, char** argv){
  // Print usage
  if(argc <= 2){
    fprintf(stderr, "Usage: ./testcase test_number filename\n1:login testcase\n");
    exit(1);
  }

  // Setup userinfo file (will create one if it does not exist) 
  // TODO: Add an option such that server can decide if it will create a new user_info file
  //       if it does not exist
  FILE* buf = fopen(argv[2], "a+");
  fclose(buf);

  // Try create a new user (if the file does not exist)
  // Try to connect to user if the file does exist
  if(fork()==0){ // Child process, fake client
    fprintf(stderr, "enter child process\n");
    sleep(2);
    int fd = easy_client();
    char buffer[MSG_SIZE];
    int len = 0;  
    int num;
    while (1)
    {
      num = read(fd, buffer+len, MSG_SIZE); 
      len += num;

      if (!num || num == -1){
          break;
      }
      if (buffer[len-1] == '\n')
          break;
    }
    buffer[len-1] = '\0';
    fprintf(stderr, "receive massage: %s\n", buffer);
    write(fd, "exit\n",5);
    len = 0;
    sleep(2);
    while (1)
    {
      num = read(fd, buffer+len, MSG_SIZE);
      len += num;

      if (!num || num == -1){
          break;
      }
      if (buffer[len-1] == '\n')
          break;
    }
    buffer[len-1] = '\0';
    fprintf(stderr, "client receive 2nd massage: %s\n", buffer);
    write(fd,"12345\n",6);
  }
  else{ // Parent process, fake server
    fprintf(stderr, "enter parent process\n");
    if(map_userinfo(argv[2])==-1){
      fprintf(stderr, "Unable to map the file\n");
      exit(1);
    }

    int fd = easy_server();
    fprintf(stderr, "server accpeted client\n");
    int result = login(fd);
    if(result == -1)
      fprintf(stderr, "Client exited or created new character\n");
    else
      fprintf(stderr, "Client connected to existing character\n");
    unmap_userinfo();
  }
  return 0;
}
