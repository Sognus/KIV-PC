#ifndef KIV_PC_LCS_H
#define KIV_PC_LCS_H

#include <stdlib.h>
#include <string.h>

/* Jedna struktura v dane tabulce */
typedef struct lcs_entry {
    unsigned int score;
    char letter;
    struct lcs_entry* prev;
} lcs_entry;

/* Vytvori nejdelsi spolecny podretezec pro dva vstupni retezce */
unsigned int longest_common_substring(char *str1, char *str2, char **result);

#endif /* KIV_PC_LCS_H */
