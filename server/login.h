// Message sent to the new client for username/password
// TODO: how to make this as a file (easier to modify??)
#define USERNAME "Please enter your username\n"
#define PASSWORD "Please enter your password\n"

// This is a helper function to map the userinfo file into memory
// It takes file name as parameter 
// Return 0 on success. Otherwise, return -1
int map_userinfo(char* filename);

// This function is called when user sucessfully connect to the server 
// It is similar to processClient function, but specify for user login
// return -1 if user exit, otherwise return file descriptor
// (corresponding to the cell in character array)
int login(int fd);
