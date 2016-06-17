
##main-01.c
    press ctrl+c to create thread, to observe the usage of resources

##main-02.c
    same as main-01.c, except set phread stack size to 2MB

##main-03-1.c
##main-03-2.c
    compare the usage of resource between 1-thread and 2-threads do the same task "sum 1 - 1000..."

##main-04.c
    compare the usage of resource betweem "before dead lock" & "dead lock"

#tools
    valgrind --tool=callgrind ./main-03-2.out 0 1000000
    kcachegrind callgrind.out.***
