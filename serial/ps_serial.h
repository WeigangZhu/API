#ifndef PS_SERIAL_H_
#define PS_SERIAL_H_

#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <time.h>


int 	dev_open(char dev[]);
void 	set_speed(int, int);
int 	set_parity(int fd, int databits, int stopbits, int parity);
void 	is_open(int fd, char *filename);  // open file ?

#endif
