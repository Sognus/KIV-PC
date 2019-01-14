#ifndef KIV_PC_STRING_HELP_H
#define KIV_PC_STRING_HELP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Overi jestli dany znak je oddelovacem slov v kodovani CP1250 */
int cp1250_is_word_separator(unsigned char c);

/* Funkce ktera vrati vetsi cislo ze dvou  */
long long_max(long a, long b);

/* Prevede znak z velkeho pismene na male */
unsigned char cp1250_tolower(unsigned char c);

#endif /* KIV_PC_STRING_HELP_H */
