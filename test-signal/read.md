
## main-01.c
    test sigmask & syscall "sleep" & "select" restart when use signal
    "sleep" & "select" not restart

## main-02.c
    test sigmask & syscall "sleep" & "select" restart when use sigaction
    select not restart, don't know why

## main-03-serv.c
### main-03-cli-signal.c
    test sigmask & syscall "read" restart when use signal
    "read" restart by default!!
### main-03-cli-sigaction.c
    test sigmask & syscall "read" restart when use sigaction
    "read" restart or not can be controlled by sa_flags

