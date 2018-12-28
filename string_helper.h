#ifndef KIV_PC_STRING_HELPER_H
#define KIV_PC_STRING_HELPER_H

#include <string.h>

/* Zmeni jeden znak za druhy  */
char* replace_char(char* str, char find, char replace);

/* Nahradi posledni vyskyt znaku */
void replace_last_char(char * str, char old_char, char new_char);

void stripnew(char * string);

#endif //KIV_PC_STRING_HELPER_H
