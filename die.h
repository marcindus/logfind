#ifndef DIE_H_INCLUDED
#define DIE_H_INCLUDED


#include <errno.h>

void die(const char *message) 

{
    if (errno) {
        perror(message);
    }    
    else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}

#endif
