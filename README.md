# myio <img src="https://github.com/Asti7/clip/blob/master/images/clip_logo.png" height="40" width="40">

Myio is a simple alternative to standard C i/o library. It utilises low level system calls to achive basic input/output functionality. 


## Why ? 

Implementing the myio libraray was part of the [FIT2100 Operating Systems](https://handbook.monash.edu/2021/units/FIT2100) curriculum, being part of Assignment 1 for summer semester B 2021.

Also, I hate using format specifiers in C for trivial input and output stuff 😬, it just leads to more keyboard presses 😆


### Manual

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

### How to install on your linux environment ?

Step 1: Compile the library without producing an executable file, by using the following command (since a library has no main function, it can’t be linked into a complete executable file by itself. This creates an ‘object file’ which can be linked to another program later to create a complete executable program):

```
gcc -c myio.c
```

Step 2: Now you will have a file named myio-123456789.o or similar. The following command will now convert it into a .a file
(static library archive)

```
ar -rsc myio.a myio.o
```

Step 3: Let’s copy the new myio.a file, as well as your existing myio-123456789.h header file, into standard locations where gcc will be able to find them. Since these locations are outside your home directory, you will need to use the sudo command (which stands for ‘super-user do’) to carry out these privileged file copy operations. Run the following commands and enter your password (which won’t be displayed in the terminal) when prompted to do so.


```
sudo cp myio.a /usr/local/lib

sudo cp myio.h /usr/local/include/myio.h
```


Now your library is installed. Here’s how to use it: addtheline : #include <myio.h> at the top of any source file that requires your library functions, and when you compile a program that requires this library, add the -lmyio argument (with a lowercase letter L) to the end of your gcc command, to tell gcc to link the final executable to your library. Have fun!



