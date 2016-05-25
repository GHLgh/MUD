// Message sent to the new client for username/password
// TODO: how to make this as a file (easier to modify??)
#define USERNAME "Please enter your username\n"
#define PASSWORD "Please enter your password\n"
#define NEWUSER  "Username does not exist, creating new character...\n"

typedef struct _user_info{
  char* username;
  char* password;
  int character_id;
  int user_status; // 0: if old user, 1: if new user
}user_info;

// It will be used as a pointer to the first element in user_info array
// It will be setup when map_userinfo succeeds
user_info* user_array;
int user_num;

// This is a helper function to map the userinfo file into memory
// It takes file name as parameter 
// Return 0 on success. Otherwise, return -1
int map_userinfo(char* filename);

// A function to clean up the allocated resource and update new user to 
// the original userinfo file
// This functgion should be called when the server is going to shut down
void unmap_userinfo();

// This function is called when user sucessfully connect to the server 
// It is similar to processClient function, but specify for user login
// return -1 if user exit, otherwise return character_id
// (corresponding to the cell in character array)
int login(int fd);
