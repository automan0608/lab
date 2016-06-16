#include <stdlib.h>
#include "p1.h"
#include "p2.h"


int main()
{
    int (*ptr)();

    ptr = p1;
    ptr = p2;

//    p1;

    ptr();
}
