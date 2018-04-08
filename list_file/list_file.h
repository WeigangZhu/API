#ifndef LIST_FILE_H_
#define LIST_FILE_H_

#include <stdio.h>  
#include <unistd.h>  
#include <dirent.h>  
#include <stdlib.h>  
#include <sys/stat.h>  
#include <string.h>  
#include <assert.h>  

#define MAX_FILE_NAME_LEN 256  
#define MAX_FILE_NUMBER 1024

typedef struct files_list
{
	unsigned long files_number;
	char files_name[MAX_FILE_NUMBER][MAX_FILE_NAME_LEN];
}
files_list_t;

files_list_t* list_files(char *dir_name);  

#endif
