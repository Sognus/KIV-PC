#ifndef KIV_PC_STRING_HELP_H
#define KIV_PC_STRING_HELP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Overi jestli dany znak je oddelovacem slov v kodovani CP1250 */
cp1250_is_word_separator(unsigned char c);

/* Prozkouma velikosti retezcu, vrati vetsi z nich  */
long max_strlen(char *str1, char *str2);

/* Funkce ktera vrati vetsi cislo ze dvou  */
long long_max(long a, long b);

#endif //KIV_PC_STRING_HELP_H
