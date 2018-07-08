#define DEBUG

#include"list_file.h"
  
files_list_t* list_files(char *dir_name)  
{  
    assert(dir_name != NULL);  
      
    char path[MAX_FILE_NAME_LEN];  
    struct dirent *file_name;
    DIR *dir;
      
    dir = opendir(dir_name);  
    if(dir == NULL)  
    {  
        printf("open dir %s error!\n", dir_name);  
        exit(1);  
    }  
    
    files_list_t* re_files_list = (files_list_t*)malloc(sizeof(struct files_list));
    if (re_files_list == NULL)
    	printf("malloc for the return files list error\n");
    	
   re_files_list->files_number = 0;
    
    while((file_name = readdir(dir)) != NULL)  
    {  
       
        if(!strcmp(file_name->d_name,".") || !strcmp(file_name->d_name,".."))  
            continue;  
              
        sprintf(path,"%s/%s", dir_name, file_name->d_name);  
          
        struct stat s;  
        lstat(path,&s);  
          
       
        if(S_ISDIR(s.st_mode))  
        {  
            /* 
            list_files(path);//递归调用  
            */
        }
          
        else  
        {  
            // printf("%s\n",file_name->d_name);  
            if(re_files_list->files_number > 1023)
            	printf("files are greater than the MAX_FILE_NUMBER: %d\n", MAX_FILE_NUMBER);
            else
            {
            	strcpy(re_files_list->files_name[re_files_list->files_number], file_name->d_name);
            	// printf("%s\n", re_files_list->files_name[re_files_list->files_number]);
            	re_files_list->files_number++;
            }
        }  
    }  
    
    
    closedir(dir); 	
    return re_files_list;
}  
  
#ifdef DEBUG
//测试部分
int main(int argc, char **argv)  
{  
  
    if(argc != 2)  
    {  
        printf("one dir required!(for eample: ./a.out /home/myFolder)\n");  
        exit(1);  
    }  
    
    files_list_t* ll = list_files(argv[1]);  
    for (int i=0; i< ll->files_number; i++)
    	printf("%s\n", ll->files_name[i]);
    	
    free(ll);
    return 0;  
}

#endif


