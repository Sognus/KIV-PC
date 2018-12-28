#include "string_helper.h"

/* Zmeni jeden znak za druhy */
char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

/* Nahradi posledni vyskyt znaku */
void replace_last_char(char * str, char old_char, char new_char)
{
    int i, lastIndex;

    lastIndex = -1;
    i = 0;

    /* Run till end of string */
    while(str[i] != '\0')
    {
        /* If an occurrence of character is found */
        if(str[i] == old_char)
        {
            lastIndex = i;
        }

        i++;
    }

    if(lastIndex != -1)
    {
        str[lastIndex] = new_char;
    }
}

void stripnew(char * string){
    if(string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = '\0';
}