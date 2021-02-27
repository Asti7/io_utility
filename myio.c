/**
NAME: Astitva Gautam

This C source file contains function bodies of myio library.
**/

#include "myio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/*This function prints a string to the terminal using write().

param: a string which is to be printed.
return: int type, number of charcters in the string.
*/
int print(char *source)
{

    for (int i = 0; i <= strlen(source); i++)
    {
        write(1, &source[i], 1);
    }

    // newline added to the end of output
    write(1, "\n", 1);

    return strlen(source);
}

/*
This function reads a single line of input from standard input and puts the string of characters into the destination character array.

param: a string, char array.
return: int type, the total number of characters the user typed.
*/
int input(char *destination)
{
    int i = 0;
    while (1)
    {
        read(0, &destination[i], 1);
        if (i > 98) // input should no longer be more than 99 characters long
        {
            break;
        }
        if (strcmp(&destination[i], "\n") == 0)
        {
            break;
        }
        i++;
    }
    destination[strlen(destination) - 1] = '\0'; // null termination of string, strlen(destination) -1 because this would be the last index in the array to put '\0'.
    int len = strlen(destination);
    if (len > 99) //if there are too many characters, assuming more than 99.
    {
        len = 99;
    }

    return len;
}

/*
This function prints the integer which is passed as a parameter in the function.

param: int number to be printed
return: int type, total number of characters of the integer.
*/

int iprint(int number)
{
    // assumes the integer is 10 characters long.
    char string[10];

    // used complimentary function to convert integer type to string type.
    integertoString(string, number);
    print(string);

    return strlen(string);
}

/*
This is a complimentary function which converts an integer to string type.

param: string of type char* which stores the string type of the integer passed.
param: int number which needs to be converted to string type.
return: void
*/
void integertoString(char *string, int num)
{

    if (num == 0)
    {
        string[0] = '0';
        return;
    };
    int divide = 0;
    int mod;
    int copyOfNumber;
    int length = 0;
    int isNegative = 0;

    int offset = 0;
    copyOfNumber = num;
    if (num < 0)
    {
        isNegative = 1;
        num = 0 - num;
        length++;
    }
    while (copyOfNumber != 0)
    {
        length++;
        copyOfNumber /= 10;
    }

    for (divide = 0; divide < length; divide++)
    {
        mod = num % 10;
        num = num / 10;
        string[length - (divide + 1)] = mod + '0';
    }
    if (isNegative)
    {
        string[0] = '-';
    }
    string[length] = '\0';
}

/*
This function reads a postive or negative integer from standard input and returns the resulting integer.

param: int type, invalidnumber specified in the function argument to return an invalidnumber if the user enters an illegal number for input.
return: int type, number which is used as input by the user or can be the invalidnumber when an illegal input is performed.
*/
int iinput(int invalidnumber)
{

    char buff[16]; // assumes initial buffer size to be 16.
    int j = 0;
    while (1)
    {

        read(0, &buff[j], 1);

        if (strcmp(&buff[j], "\n") == 0)
        {
            break;
        }
        j++;
    }

    for (int i = 0; i <= strlen(buff); i++)
    {
        if ((buff[0] == '-') || (buff[i] >= '0' && buff[i] <= '9'))
        {

            /*converts character string to integer using number formation.*/
            int number = 0;
            int neg = buff[0] == '-';
            int i = neg ? 1 : 0; // ternary check for neg.
            while (buff[i] >= '0' && buff[i] <= '9')
            {
                number *= 10;            // multiply number by 10
                number += buff[i] - '0'; // convet ASCII '0'..'9' to digit 0..9 and add it to number
                i++;                     // step one digit forward
            }
            if (neg)
                number *= -1;
            return number;
        }
        else
        {
            return invalidnumber;
        }
    }

    return 0;
}

/*
This function takes a filename and a line to append to the file.

param: string filename i.e., name of the file
param: string line to be appended
return: int type, returns 0 if file opened successfully or else -1 if it failed to open.
*/
int appendfile(char *filename, char *line)
{
    int writefile = open(filename, O_RDWR | O_CREAT | O_APPEND);
    if (writefile > 0)
    {
        // lseek(writefile, 0, SEEK_END); is not neccessary because of the O_APPEND int flag in open().

        write(writefile, line, strlen(line));
        write(writefile, "\n", 1);
        return 0; // returns 0 if succeeded.
    }

    if (writefile < 0)
    {
        return -1; // returns -1 if open failed to append.
    }

    return 0;
}

/*
This function takes a filename and an integer value to append to the file.

param: string filename i.e., name of the file
param: int value to be appended
return: int type, returns 0 if file opened successfully or else -1 if it failed to open.
*/
int iappendfile(char *filename, int value)
{
    char stringToAppend[100]; // assumes integer value to be no more than 100 characters.

    int writefile = open(filename, O_RDWR | O_CREAT | O_APPEND);
    if (writefile > 0)
    {
        // converts integer value to string, so that it can be appended to a file.
        integertoString(stringToAppend, value);
        appendfile(filename, stringToAppend);
        return 0; // returns 0 if succeeded.
    }
    if (writefile < 0)
    {
        return -1; // returns -1 if open failed to append.
    }
    return 0;
}

/*
This function opens the filename given in the first argument, and reads the entire file into the character array given in the second argument. The third argument specifies the number of elements in the destination array. If the file contains equal or more characters than elements in this array, all further characters are ignored.

param: char* filename, char* destination is an array, int maxsize
return: int type, return -1 if file failed to open, return 0 meaning the entire file's content were read into destination and returns 1 meaning only a part of the file could be read into the destination array, as the number of characters
in the file was greater than or equal to maxsize. 
*/

int readfile(char *filename, char *destination, int maxsize)
{

    destination = (char *)malloc(maxsize); // allocates memory for destination array the size of maxsize

    char buff[1024]; // assumes initial buffer size to be 1024

    int readfile = open(filename, O_RDONLY);
    if (readfile < 0)
    {
        return -1;
    }

    for (int i = 0; i < maxsize; i++)
    {
        read(readfile, &buff[i], 1);
        destination[i] = buff[i];
    }
    destination[strlen(destination) - 1] = '\0'; // null termination strlen(destination) -1 because this would be the last index in the array to put '\0'.
    print(destination);

    if (strlen(buff) < maxsize)
    {
        // covers entire content in the file
        return 0;
    }
    else
    {
        // the content in the file exceeds maxsize
        return 1;
    }
    free(destination); // free malloc
    return 0;
}

/*This is a complimentary function which opens the filename given in the first argument, and reads the entire file into the character array given in the second argument. The third argument specifies the number of elements in the destination array.

param: char* filename, char* destination is an array, int maxsize
return: char* type, returns the destination array. 
 */
char *readfile_and_print_array(char *filename, char *destination, int maxsize)
{
    destination = (char *)malloc(maxsize); // allocates memory for destination array the size of maxsize

    char buff[1024]; // assumes initial buffer size to be 1024

    int readfile = open(filename, O_RDONLY);
    if (readfile < 0)
    {
        exit(1);
    }

    for (int i = 0; i < maxsize; i++)
    {
        read(readfile, &buff[i], 1);
        destination[i] = buff[i];
    }
    destination[strlen(destination) - 1] = '\0'; // null termination strlen(destination) -1 because this would be the last index in the array to put '\0'.

    free(destination); // free malloc
    return destination;
}
