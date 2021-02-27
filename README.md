# myio

Myio is a simple alternative to standard C i/o library. It utilises low level system calls to achive basic input/output functionality. 


## Why ? 

Implementing the myio libraray was part of the [FIT2100 Operating Systems](https://handbook.monash.edu/2021/units/FIT2100) curriculum, being part of Assignment 1 for summer semester B 2021.

Also, I hate using format specifiers in C for trivial input and output stuff 😬, it just leads to more keyboard presses 😆


```

Name
        myio -- custom input/output library functions

SYNOPSIS 
        #include <myio.h>

DESCRIPTION 
        This library is an alternative to the standard i/o library for C. It utlises low level system calls to achieve input/output functionality. 

LIST OF FUNCTIONS
        Function        Description 
        print           prints to output 
        input           takes standard input
        iprint          prints integer to output 
        iinput          takes standard integer input 
        appendfile      appends to a file
        iappendfile     appends an integer to a file
        readfile        reads from a file and stores the read content in an array 

AUTHOR 
        Astitva Gautam 
        Jan-2021

```



