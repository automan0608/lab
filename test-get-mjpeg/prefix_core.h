
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define SUCCESS     0
#define ERROR       -1

#define DEBUG(fmt, args...)  do {            \
    printf("%s:%d | " fmt "\n", __FUNCTION__, __LINE__, ##args);         \
} while (0);
