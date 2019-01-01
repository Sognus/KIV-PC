#ifndef KIV_PC_LCS_H
#define KIV_PC_LCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lcs_entry {
    unsigned int score;
    char letter;
    struct lcs_entry* prev;
};
typedef struct lcs_entry lcs_entry;


unsigned int longest_common_substring(char *str1, char *str2, char **result);

#endif //KIV_PC_LCS_H
