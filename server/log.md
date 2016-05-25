### May 25
**Finished the login functionality**
* So now the procedure [server_accpet => login => server_know_which_character_should_be_loaded] should be able to perform (if nothing goes wrong)

**TODO:**
* Create some testcases to see if it actually work
* Make it multi-threaded because it should be called in process_client thread (different from the original thought: call login function when server accepts a new connection)

### May 23
**Changed the way to load user info from file**
* Originally used mmap. However, since the program needs to keep track on the location of corresponding information if it uses mmap,
I thought it would be better to traverse the whole file and cast it into multiple user_info nodes 
such that they can be used easier later (or not).
