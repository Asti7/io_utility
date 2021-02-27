/**
NAME: Astitva Gautam
This header file containes function prototypes for myio library.
**/

int print(char *source);

int input(char *destination);

int iprint(int number);

int iinput(int invalidnumber);

void integertoString(char *string, int num);

int appendfile(char *filename, char *line);

int iappendfile(char *filename, int value);

int readfile(char *filename, char *destination, int maxsize);

char *readfile_and_print_array(char *filename, char *destination, int maxsize);