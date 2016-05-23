### May 23
**Changed the way to load user info from file**
* Originally used mmap. However, since the program needs to keep track on the location of corresponding information if it uses mmap,
I thought it would be better to traverse the whole file and cast it into multiple user_info nodes 
such that they can be used easier later (or not).
