#### This project is about implementing a thread-safe dynamic memory allocation mechanism.
To claim and return the memory zones to the system used ```mmap()``` and ```munmap()``` syscals. To make it tread-safe pthread_mutex_t is used. Functions prototyped just like the systems ones:
```c
void *malloc(size_t size);
```
```c
void *realloc(void *ptr, size_t size);
```
```c
void free(void *ptr);
```
* The ```malloc()``` function allocates “size” bytes of memory and returns a pointer to the allocated memory.
 
* The ```realloc()``` function tries to change the size of the allocation pointed to by “ptr” to “size”, and returns “ptr”. If there is not enough room to enlarge the memory allocation pointed to by ptr, realloc() creates a new allocation, copies as much of the old data pointed to by “ptr” as will fit to the new allocation, frees the old allocation, and returns a pointer to the allocated memory.
 
* The ```free()``` function deallocates the memory allocation pointed to by “ptr”. If “ptr”is a NULL pointer, no operation is performed.
 
* In case of an error, the ```malloc()```, ```realloc()``` functions return a NULL pointer.

Main information sources were:
* [Modern Operating Systems (4th Edition) by Andrew S. Tanenbaum, Herbert Bos](https://www.amazon.com/Modern-Operating-Systems-Andrew-Tanenbaum/dp/013359162X)
* [man (2) mmap](https://linux.die.net/man/2/mmap)
* [man (3) munmap](https://linux.die.net/man/3/munmap)


[![https://profile.intra.42.fr/users/vpopovyc](https://lh3.googleusercontent.com/gPspq5E1uQBEpIz98Nbqbl7WlWn64JvAiD34pFCYFvX3NKCp9SkCY07-Adkwr3gQr0UY=w100)](https://profile.intra.42.fr/users/vpopovyc) 
