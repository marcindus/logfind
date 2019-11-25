#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <unistd.h>
#include "dbg.h"
#include "die.h"

const size_t MAX_BUFFER = 32;

int scan_config_files(glob_t *buffer);
char *my_getline(FILE *infile);
FILE *open_file(char *fname);
int search_in_file(char *string[], int string_len, char *fname, int or_option);
int find_all_in_line(char *line, char *string[], int string_len, int or_option);


char *my_getline(FILE *infile) 
{

    char *line;
    line = calloc(MAX_BUFFER, sizeof(char));
    check(line, "initial Malloc for line failed!");

    char *line_buffer;
    line_buffer = calloc(MAX_BUFFER, sizeof(char));
    check(line_buffer, "initial Malloc for line buffer failed!");

    if (fgets(line_buffer, MAX_BUFFER, infile)!=NULL) 
    {
        int counter = 2;
        strcat(line, line_buffer);
        while(!strstr(line_buffer, "\n")) 
        {
                line = realloc(line, counter*MAX_BUFFER*(sizeof(char)));
                counter++;
                fgets(line_buffer, MAX_BUFFER, infile);
                strcat(line, line_buffer);
        }
    }
    else
    {
        free(line_buffer);
        free(line);
        return  NULL;
    }
    free(line_buffer);
    return line;

error:
    if(line_buffer) free(line_buffer);
    if(line) free(line);
    return  NULL;
}


FILE *open_file(char *fname) 
{
    FILE *input_file;
    if(access(fname, F_OK) != -1) {
        input_file = fopen(fname, "r");
        check(input_file, "Failed to open %s", fname);
        return input_file;
    }
    else 
    {
        die("File does not exist");
    }
error:
    if(input_file) free(input_file);
    return NULL;
}


int search_in_file(char *strings[], int string_len, char *fname, int or_option) 
{
    unsigned int line_number = 0;
    FILE *input_file =  open_file(fname);
    char *line = my_getline(input_file);
    check(line, "Failed to read from file");

    while(line) 
    {
        if (find_all_in_line(line, strings, string_len, or_option) != -1)
        {
                printf("%s:%d\t%s",fname, line_number, line);
        }
        line = my_getline(input_file);
        line_number++;
    }
    free(line);
    fclose(input_file);
    return 0;
error:
    free(line);
    fclose(input_file);
    return -1;
}

int is_present(char *line, char *str) 
{
    if(strstr(line, str) != NULL)
    {
        return 1;
    }
    return 0;
}

int find_all_in_line(char *line, char *strings[], int strings_size, int or_option)
{
    int found = 0;
    for(int i=0; i<strings_size ; i++) 
    {
        found = found + is_present(line, strings[i]);
    }
    if((found == strings_size) ) 
    {
        debug("found: %d, string_size %d",found,strings_size);
        return 1;
    }
    else if( found == 0) 
    {
        return -1;
    }
    else if((found < strings_size) && or_option == 1) 
    {
        return 1;
    }
    return -1;
}

int scan_config_files(glob_t *buffer) 
{

    FILE *config_file = open_file(".logfind");

    char *config_line  = my_getline(config_file);
    config_line[strlen(config_line) - 1] = '\0';
    glob(config_line, GLOB_TILDE, NULL, buffer); //rafactor.. 

    while(config_line) 
    {
        config_line  = my_getline(config_file);
        if(config_line) {
            config_line[strlen(config_line) - 1] = '\0';
            glob(config_line, GLOB_TILDE | GLOB_APPEND, NULL, buffer);
        }
    }

    fclose(config_file);
    free(config_line);

return 0;

}

int main(int argc, char *argv[])
{
//parse argument - separate function
//refactor!!
//unit tests!!
    if(argc < 2) die("Wrong arguments numer, usage ./logfind  string_to_search");
    int or_option = 0;
    glob_t globbuf;
    scan_config_files(&globbuf);
    
    argv++;
    argc--;
    if(strcmp(argv[0], "-o") == 0)
        {
        or_option = 1;
        argv++;
        argc--; 
        }
    for(int i =0 ; i < globbuf.gl_pathc ; i++) {
        search_in_file(argv,argc, globbuf.gl_pathv[i], or_option);
    }
    globfree(&globbuf);

return 0;
}
