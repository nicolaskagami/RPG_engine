//Nicolas Silveira Kagami
//Input Output Source
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "io.h"

IO::IO()
{
    file_confirm = 0;
}
int IO::read()
{
    if(file_confirm)
    {
        if(fgets(entrystr,MAX_LINE_SIZE,input_file))
        {
           numparam = 0;
           buffer = strtok(entrystr," ,./");
           while(buffer&&numparam<=MAX_PARAMETERS)
           {
                parameters[numparam] = atoi(buffer);
                buffer = strtok(NULL," ,./");
                numparam++;
           }
           return 1;
        }
        else
        {
            return 0; 
        }
    }
    else
    {
        printf("No file opened yet\n");
        return 0;
    }
}
int IO::open_file(char * filename)
{
    if(strlen(filename)<=MAX_FILENAME)
    {
        input_file = fopen(filename,"r");
        if(input_file)
        {
            file_confirm = 1;
            return file_confirm;
        }
    }
    file_confirm = 0;
    printf("Invalid file name\n");
    return file_confirm;
}
